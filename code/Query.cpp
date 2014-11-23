#include "Query.h"
#include <vector> 
#include <string>

using namespace std;

Query::Query()
{

}

Query::Query(std::vector<std::string> andVec, std::vector<std::string> orVec, std::vector<std::string> notVec)
{
	andArgs = andVec;
	orArgs = orVec;
	notArgs = notVec;
}

std::vector<std::string> Query::getandArgs()
{
	return andArgs;

}

std::vector<std::string> Query::getorArgs()
{
	return orArgs;

}

std::vector<std::string> Query::getnotArgs()
{
	return notArgs;
}

void Query::addandArgs(std::string andArg)
{
	andArgs.push_back(andArg);
}
void Query::addorArgs(std::string orArg)
{
	orArgs.push_back(orArg);
}
void Query::addnotArgs(std::string notArg)
{
	notArgs.push_back(notArg);
}
void Query::addnormArgs(std::string normArg)
{
	normArgs.push_back(normArg);
}

Query::~Query()
{

}