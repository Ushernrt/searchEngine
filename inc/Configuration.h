 ///
 /// @file    Configuration.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 14:50:12
 ///

#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__

#include <string>
#include <map>
#include <set>

using std::string;
using std::map;
using std::set;

namespace wd{

class Configuration{
public:
	Configuration(const string & filepath);
	
	map<string, string> & getConfigMap();

	set<string> getStopWordList();

	void showConfigMap();

private:
	void initConfigMap();

	void initStopWordList();

private:
	string _filepath;
	map<string, string> _configMap;
	set<string> _stopWordList;	
};

}// end of namespace wd
#endif

