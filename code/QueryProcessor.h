#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <vector>
#include <string>
#include <sstream> 
#include <iostream>

using namespace std;


class QueryProcessor
{
public:
	QueryProcessor();
	~QueryProcessor();
	void parseQuery(std::string);
private:
	std::string searchQuery;
	std::vector<std::string> searchWords;

};

#endif 