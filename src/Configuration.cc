 ///
 /// @file    Configuration.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 14:57:37
 ///

#include "../inc/Configuration.h"

#include <fstream>
#include <memory>
#include <iostream>

using std::ifstream;
using std::unique_ptr;
using std::cout;
using std::endl;

namespace wd{

Configuration::Configuration(const string & filepath)
: _filepath(filepath)
{
	initConfigMap();
	initStopWordList();
//	showConfigMap();
}

map<string, string> & Configuration::getConfigMap(){
	return _configMap;
}

set<string> Configuration::getStopWordList(){
	
	return set<string>();
}

void Configuration::initConfigMap(){
	unique_ptr<ifstream> ifs(new ifstream(_filepath));
	
	if(!ifs->good()){
		cout << "ifstream error Configuration" << endl;
		return ;
	}
	
	string key,value;

	while(!ifs->eof()){
		*ifs >> key;
		*ifs >> value;
		
		_configMap[key] = value;
	}
}

void Configuration::initStopWordList(){
	
}

void Configuration::showConfigMap(){
	for(auto item : _configMap){
		cout << item.first << " : " << item.second << endl;
	}
}

}// end of namespace wd
