 ///
 /// @file    testDir.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 16:16:49
 ///

#include "../inc/Configuration.h"
#include "../inc/DirScanner.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
	wd::Configuration conf("../conf/config");
	wd::DirScanner dir(conf);

	dir();

	dir.displayFiles();
	
	return 0;
}
