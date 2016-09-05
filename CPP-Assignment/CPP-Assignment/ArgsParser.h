 /* ---------------------------------------------------------------------------
 ** <ArgsParser>.h
 ** <Helper class that nicely deals with process command line arguments>
 **
 ** Author: <Kirolos Kaldas (s3545643) & Josh Caratelli (s3492633)>
 ** Assignment 1, COSC1252/1254 Programming Using C++
 ** -------------------------------------------------------------------------*/

#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include <string>
#include <vector>
#include <algorithm>  
using namespace std;

class ArgsParser
{
public:
	ArgsParser(int& argc, char** argv);
	~ArgsParser();

	//Get param from the cmd option, e.g. if --g is specified get the int width after
	const std::string GetCmdOption(const std::string& cmdOption) const;
	//e.g. check if --sv --sb --g exists
	bool CmdOptionExists(const std::string& cmdOption) const;

protected:

private:
	vector <std::string> m_tokens;
};
#endif
