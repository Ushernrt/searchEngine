 ///
 /// @file    WebPage.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-03 21:50:24
 //

#include "../inc/WebPage.h"
#include "../inc/Configuration.h"
#include "../inc/cppjieba/Jieba.hpp"

#include <ctype.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <memory>
using std::istringstream;
using std::sort;
using std::ifstream;
using std::unique_ptr;

const char* const DICT_PATH = "/home/xiu/searchEngine/dict/jieba.dict.utf8";
const char* const HMM_PATH = "/home/xiu/searchEngine/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/xiu/searchEngine/dict/user.dict.utf8";
const char* const IDF_PATH = "/home/xiu/searchEngine/dict/idf.utf8";
const char* const STOP_WORD = "/home/xiu/searchEngine/dict/stop_words.utf8";

using PAIR = std::pair<string, int>;

struct CmpByValue{
	bool operator()(const PAIR & lhs, const PAIR & rhs){
		return lhs.second > rhs.second;
	}

};


namespace wd{

	cppjieba::Jieba jieba(DICT_PATH,
				HMM_PATH,
				USER_DICT_PATH,
				IDF_PATH,
				STOP_WORD);	


	WebPage::WebPage(string & doc, Configuration & config)
	: _doc(doc)
	{
		
		unique_ptr<ifstream> ifs(new ifstream(config.getConfigMap()["stopwords"]));
		if(!ifs->good()){
			std::cout << "ifs error stopwords" << std::endl;
			return ;
		}
		string words;
		while(ifs->eof()){
			*ifs >> words;
			_stopwords.push_back(words);
		}

		
		unique_ptr<ifstream> ifsen(new ifstream(config.getConfigMap()["stopwordsen"]));

		if(!ifs->good()){
			std::cout << "ifs error stopwords" << std::endl;

			return ;
		}
		while(ifsen->eof()){
			*ifsen >> words;
			_stopwords.push_back(words);
		}

		processDoc(doc, config);		

	}

	int WebPage::getDocId(){
		return _docid;
	}

	string WebPage::getDoc(){
		return _doc;
	}

	map<string,int> & WebPage::getWordsMap(){
		return _wordsMap;		
	}

	void WebPage::processDoc(const string & doc, Configuration & config){
		istringstream iss(doc);
		string docid;
		iss >> docid;
		std::cout << "processing " << docid << std::endl;
		_docid = ::atoi(docid.c_str());

		iss >> _docUrl;
		iss >> _docTitle;
		_docContent = iss.str();
		//	std::cout << _docContent << std::endl;
		vector<string> words;
		jieba.Cut(_docContent, words);
	
		for(auto item : words){
			_wordsMap[item]++;
		}
			
		removeStopWords();

		calcTopK();
	}

	void WebPage::removeStopWords(){
		for(auto item : _stopwords){
			_wordsMap.erase(item);
		}
	}

	void WebPage::calcTopK(){

		vector<PAIR> vec_tmp(_wordsMap.begin(),_wordsMap.end())	;
		sort(vec_tmp.begin(), vec_tmp.end(), CmpByValue());

		int i = 0;
			
		for(i = 0; i < (TOPK_NUMBER > (int)vec_tmp.size() ? (int)vec_tmp.size() : TOPK_NUMBER); ++ i){
			_topWords.push_back(vec_tmp[i].first);
		}
		
	}

	bool operator==(const WebPage & lhs, const WebPage & rhs){
		int idx = 1;

		for(auto iteml : lhs._topWords){
			for(auto itemr : rhs._topWords)
			{
				if(iteml == itemr){
					++ idx;
					if(idx == 6){
						return true;
					}
				}
			}
		}
		return false;	

	}

	bool operator<(const WebPage & lhs, const WebPage & rhs){
		return lhs._docid < rhs._docid;
	}


}// end of namespace wd

