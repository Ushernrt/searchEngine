 ///
 /// @file    PageLib.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 16:57:08
 ///

#include "../inc/PageLib.h"
#include "../inc/Configuration.h"
#include "../inc/DirScanner.h"
#include "../inc/tinyxml2.h"
#include "../inc/WebPage.h"

#include <unistd.h>

#include <iostream>
#include <regex>
#include <fstream>
#include <memory>
#include <sstream>

using std::cout;
using std::endl;
using std::regex;
using std::regex_replace;
using std::unique_ptr;
using std::ofstream;
using std::ostringstream;
using namespace tinyxml2;

namespace wd{

	PageLib::PageLib(Configuration & conf, DirScanner & dirScanner)
	: _conf(conf)
	, _dirScanner(dirScanner)
	{

	}

	void PageLib::createLib(const string & filename){
		XMLDocument doc;
		doc.LoadFile(filename.c_str());
		cout << "deal " << filename << " ing ..." << endl;
		XMLElement * rss = doc.RootElement();
		XMLElement * channel = rss->FirstChildElement("channel");
		XMLElement * item = channel->FirstChildElement("item");
		while(item){
			MyPage article;
			XMLElement * itemChild = item->FirstChildElement("title");
			if(itemChild){
				article._title = itemChild->GetText();
			}
			itemChild = item->FirstChildElement("link");
			if(itemChild){
				article._url = itemChild->GetText();
			}
			itemChild = item->FirstChildElement("content:encoded");
			if(itemChild){
				article._content = itemChild->GetText();
				regex re("<.*?>");
				article._content = regex_replace(article._content, re, "");
			}
			_vecArticles.push_back(article);
			
			item = item->NextSiblingElement();
		}
	}
	string int2string(const int id){
		ostringstream oss ;
		oss << id;
		return oss.str();
	}


	void PageLib::create(){
		vector<string> files = _dirScanner.files();
		for(string & filename : files){
			createLib(filename);		
		}
		

	}

	void PageLib::createNewLib(){
#if 0
		vector<int> rmidx;
		cout << "found chongfude docid" << endl;
		for(auto item : _webPage){
			for(auto item2 : _webPage){
				if(item.getDocId() != item2.getDocId()){
					if(item == item2){
						rmidx.push_back(item2.getDocId());
						

					}
				}
			}
		}
		cout << "qu chonging ... " << endl;
		for(int item : rmidx){
			vector<WebPage>::iterator it = _webPage.begin();
			
			while(it != _webPage.end()){
				if(it->getDocId() == item){
					_webPage.erase(it);
					cout << it->getDocId() << endl;
					break;
				}
				++it;
			}
		
		}
#endif	
		cout << "quchong..." << endl;
		vector<WebPage>::iterator it = _webPage.begin();

		while(it != _webPage.end()){
			vector<WebPage>::iterator it2 = _webPage.begin();
			while(it2 != _webPage.end()){
				if(it->getDocId()!=it2->getDocId()){	
					if(*it == *it2){
						cout << "rm " << it2->getDocId() << endl;
						std::swap(*it2,*(--_webPage.end()));
						_webPage.pop_back();
					}
				}
				++it2;
			}
			++it;
		}
		

		int docid = 1;
		string txt ;
		
		unique_ptr<ofstream> ofs(new ofstream(_conf.getConfigMap()["newripepage"]));
		if(!ofs->good()){
			cout << "ofs ripepage error" << endl;
			return;
		}
		for(auto & item : _webPage){
			txt = "<doc>\n\t<docid>" + int2string(docid) +
				"</docid>\n\t<url>" + item.getUrl()+
				"\n\t</url>\n\t<title>" + item.getTitle()+
				"\n\t</title>\n\t<summary>" + item.getSummary() + 
				"\n\t</summary>\n\t<content>" + item.getContent() +
				"\n\t</content>\n</doc>\n";


			_offsetLib[docid] = std::make_pair(ofs->tellp(), txt.size());
			*ofs << txt ;
			
			++ docid;
		}

		
		unique_ptr<ofstream> ofsOffset(new ofstream(_conf.getConfigMap()["newoffset"]));
		for(auto & item : _offsetLib){
			*ofsOffset << item.first << " " << item.second.first << " " << item.second.second << endl;
		}



	}


	void PageLib::store(){
		unique_ptr<ofstream> ofs(new ofstream(_conf.getConfigMap()["ripepage"]));
		if(!ofs->good()){
			cout << "ofs ripepage error" << endl;
			return;
		}

		int docid = 1;
		string txt ;
		
		string page;
		for(auto & item : _vecArticles){
			txt = "<doc>\n\t<docid>" + int2string(docid) +
				"</docid>\n\t<url>" + item._url +
				"\n\t</url>\n\t<title>" + item._title +
				"\n\t</title>\n\t<content>" + item._content +
				"\n\t</content>\n</doc>\n";
			page = int2string(docid) +
				" " + item._url +
				" " + item._title +
				" " + item._content;

			WebPage pagex(page, _conf);
			_webPage.push_back(pagex);

			_offsetLib[docid] = std::make_pair(ofs->tellp(), txt.size());
			*ofs << txt ;
			
			++ docid;
		}

#if 0
		unique_ptr<ofstream> ofsifreq(new ofstream("/home/xiu/searchEngine/data/ifreq.txt"));

		for(auto item : _webPage){
			*ofsifreq << "\n\n";
			for(auto item2 : item.getTopWords()){
				*ofsifreq << item2;	
			}
			*ofsifreq << "\n\n";
		}
#endif
		unique_ptr<ofstream> ofsOffset(new ofstream(_conf.getConfigMap()["offset"]));
		for(auto & item : _offsetLib){
			*ofsOffset << item.first << " " << item.second.first << " " << item.second.second << endl;
		}
		_offsetLib.clear();	
		createNewLib();
		cout << "write completed" << endl;
	}



}// end of namespace wd
