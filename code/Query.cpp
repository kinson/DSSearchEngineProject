#include "Query.h"

using namespace std;

Query::Query()
{
	notArgs.push_back("sdas");
	cout << notArgs[0] << endl;

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


void Query::printQuery()
{

	cout << "Add Args" << endl << endl;
	if(andArgs.size()>0)
	for(int i = 0; i < andArgs.size(); i++)
	{
		cout << andArgs[i] << endl;
	}

	if(orArgs.size()>0)
	cout << "Or Args " << endl << endl;
	for(int j = 0; j < orArgs.size(); j++)
	{
		cout << orArgs[j] << endl;
	}

	if(notArgs.size()>0)
	cout << "Not Args " << endl << endl;
	for(int k = 0; k < notArgs.size(); k++)
	{
		cout << notArgs[k] << endl;
	}

	if(normArgs.size()>0)
	cout << "Not messed with " << endl << endl;
	for(int m = 0; m < normArgs.size(); m++)
	{
		cout << normArgs[m] << endl;
	}

}

void Query::clearQuery()
{
	andArgs.erase(andArgs.begin());
	orArgs.erase(orArgs.begin());
	notArgs.erase(notArgs.begin());
	normArgs.erase(normArgs.begin());

}

Query::~Query()
{

}