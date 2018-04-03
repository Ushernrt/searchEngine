 ///
 /// @file    PageLib.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 16:57:08
 ///

#include "../inc/PageLib.h"
#include "../inc/Configuration.h"
#include "../inc/DirScanner.h"
#include "../inc/tinyxml2.h"

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


	void PageLib::create(){
		vector<string> files = _dirScanner.files();
		for(string & filename : files){
			createLib(filename);		
		}

	}

	string int2string(const int id){
		ostringstream oss ;
		oss << id;
		return oss.str();
	}

	void PageLib::store(){
		unique_ptr<ofstream> ofs(new ofstream(_conf.getConfigMap()["ripepage"]));
		if(!ofs->good()){
			cout << "ofs ripepage error" << endl;
			return;
		}

		int docid = 1;
		string txt ;

		for(auto & item : _vecArticles){
			txt = "<doc>\n\t<docid>" + int2string(docid) +
				"</docid>\n\t<url>" + item._url +
				"\n\t</url>\n\t<title>" + item._title +
				"\n\t</title>\n\t<content>" + item._content +
				"\n\t</content>\n</doc>\n";

			_offsetLib[docid] = std::make_pair(ofs->tellp(), txt.size());
			*ofs << txt ;
			
			++ docid;
		}


		unique_ptr<ofstream> ofsOffset(new ofstream(_conf.getConfigMap()["offset"]));
		for(auto & item : _offsetLib){
			*ofsOffset << item.first << " " << item.second.first << " " << item.second.second << endl;
		}
		
		cout << "write completed" << endl;
	}



}// end of namespace wd
