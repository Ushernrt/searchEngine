 ///
 /// @file    DirScanner.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-04-02 15:31:19
 ///

#ifndef __WD_DIRSCANNER_H__
#define __WD_DIRSCANNER_H__

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace wd{

class Configuration;

class DirScanner{
public:
	DirScanner(Configuration & conf);

	void operator()();

	vector<string> & files();

	void traverse(const string & dirname);

	void displayFiles();

private:
	vector<string> _vecFiles;
	Configuration & _conf;

};

}// end of namespace wd

#endif
