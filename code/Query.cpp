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

Query::~Query()
{

}