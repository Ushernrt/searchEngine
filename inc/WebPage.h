 ///
 /// @file    WebPage.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-03 14:31:52
 ///

#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include <string>
#include <vector>
#include <map>
#include <set>

using std::vector;
using std::map;
using std::string;
using std::set;
namespace wd{
class Configuration;

class WebPage{

public:
	const static int TOPK_NUMBER = 20;
	WebPage(string & doc, Configuration & config);
	int getDocId();
	
	string getDoc();
	map<string,int> & getWordsMap();
	void processDoc(const string & doc,Configuration & config);
	vector<string> & getTopWords(){
		return _topWords;
	}

	string getUrl(){
		return _docUrl;
	}
	string getTitle(){
		return _docTitle;
	}

	string getContent(){
		return _docContent;
	}

	string getSummary(){
		return _docSummary;
	}

	void removeStopWords();
	void calcTopK( );
	
	friend bool operator==(const WebPage & lhs, const WebPage & rhs);
	friend bool operator<(const WebPage & lhs, const WebPage & rhs);
private:
	string _doc;
	int _docid;
	string _docTitle;
	string _docUrl;
	string _docContent;
	string _docSummary;
	vector<string> _topWords;
	map<string, int> _wordsMap;
	vector<string> _stopwords;
};
}//end of namespace wd
#endif

