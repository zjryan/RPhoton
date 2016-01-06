#ifndef ZJR_PARSER_
#define ZJR_PARSER_

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class Parser
{
public:
	Parser(std::string filePath);
	virtual ~Parser() = 0;

protected:
	std::string				path;
};

inline Parser::Parser(std::string filePath)
	:	path(filePath)
{
}

inline Parser::~Parser()
{
}

#endif
