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

void Query::printQuery()
{

	cout << "Add Args" << endl << endl;
	for(int i = 0; i < andArgs.size(); i++)
	{
		cout << andArgs[i] << endl;
	}

	cout << "Or Args " << endl << endl;
	for(int j = 0; j < orArgs.size(); j++)
	{
		cout << orArgs[j] << endl;
	}

	cout << "Not Args " << endl << endl;
	for(int k = 0; k < notArgs.size(); k++)
	{
		cout << notArgs[k] << endl;
	}

	cout << "Not messed with " << endl << endl;
	for(int m = 0; m < normArgs.size(); m++)
	{
		cout << normArgs[m] << endl;
	}
	
}

Query::~Query()
{

}