 ///
 /// @file    PageLib.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 16:47:45
 ///

#ifndef __WD_PAGELIB_H__
#define __WD_PAGELIB_H__

#include <vector>
#include <string>
#include <map>
#include <utility>

using std::vector;
using std::string;
using std::map;
using std::pair;

namespace wd{

class WebPage;
class Configuration;
class DirScanner;

struct MyPage{
	string _title;
	string _url;
	string _content;
};

class PageLib{

public:
	PageLib(Configuration & conf, DirScanner & dirScanner);
	
	void create();

	void store();
private:

	void createLib(const string & filename);
	void createNewLib();

private:
	Configuration & _conf;
	DirScanner & _dirScanner;
	vector<MyPage> _vecArticles;
	map<int, pair<int, int>> _offsetLib;
	vector<WebPage> _webPage;
};

}// end of namespace wd

#endif

