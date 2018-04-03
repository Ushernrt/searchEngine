 ///
 /// @file    DirScanner.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 15:38:36
 ///

#include "../inc/DirScanner.h"
#include "../inc/Configuration.h"

#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#include <iostream>

namespace wd{
	
	DirScanner::DirScanner(Configuration & conf)
	: _conf(conf)
	{

	}
	
	void DirScanner::operator()(){
		traverse(_conf.getConfigMap()["yuliaoku"]);
	}

	vector<string> & DirScanner::files(){
		return _vecFiles; 
	}

	void DirScanner::traverse(const string & dirname){
		DIR * dir;
		struct dirent * ptr;
		dir = opendir(dirname.c_str());
		if(NULL == dir){
			perror("open dir error");
			exit(1);
		}
		
		while((ptr = readdir(dir)) != NULL){
			if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){
				continue;
			}else if(ptr->d_type == 8){//文件
				string filename = string(dirname) + string(ptr->d_name);
				_vecFiles.push_back(filename);
			}else if(4 == ptr->d_type){
				string dir = string(dirname) + string(ptr->d_name);
				traverse(dir);
			}
		}
		closedir(dir);
	}

	void DirScanner::displayFiles(){
		for(auto item : _vecFiles){
			std::cout << item << std::endl;
		}
	}

}//end of namespace wd
