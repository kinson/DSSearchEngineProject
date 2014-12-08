#include "Query.h"

using namespace std;

Query::Query()
{

}

//returns requested vector
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

std::vector<std::string> Query::getnormArgs()
{
	return normArgs;
}

//adding keywords words to each vector
void Query::addandArgs(std::string andArg)
{
	andArgs.push_back(andArg);
}
void Query::addorArgs(std::string orArg)
{
	orArgs.push_back(orArg);
}
void Query::addnotArgs(string notArg)
{
	notArgs.push_back(notArg);
}
void Query::addnormArgs(std::string normArg)
{
	normArgs.push_back(normArg);
}

//getting words by specific index
std::string Query::getandArgs(int index)
{
	return andArgs[index];
}
std::string Query::getorArgs(int index)
{
	return orArgs[index];
}
std::string Query::getnotArgs(int index)
{
	return notArgs[index];
}
std::string Query::getnormArgs(int index)
{
	return normArgs[index];
}

//setting specific word to specific index
void Query::setandArgs(int index, std::string newWord)
{
	andArgs[index] = newWord;
}
void Query::setorArgs(int index, std::string newWord)
{
	orArgs[index] = newWord;
}
void Query::setnotArgs(int index, std::string newWord)
{
	notArgs[index] = newWord;
}
void Query::setnormArgs(int index, std::string newWord)
{
	normArgs[index] = newWord;
}


void Query::clearQuery()
{
	andArgs.clear();
	orArgs.clear();
	notArgs.clear();
	normArgs.clear();

}

Query::~Query()
{

}
