 ///
 /// @file    offline.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 20:32:25
 ///

#include "../inc/PageLib.h"
#include "../inc/Configuration.h"
#include "../inc/DirScanner.h"


#include <iostream>
using std::cout;
using std::endl;


int main(){
	wd::Configuration conf("/home/xiu/searchEngine/conf/config");
	wd::DirScanner dirs(conf);
	dirs();
	wd::PageLib pl(conf, dirs);
	
	pl.create();
	pl.store();


	return 0;

}
