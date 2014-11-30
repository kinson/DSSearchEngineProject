#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <vector>
#include <string>
#include <sstream> 
#include <iostream>
#include "Query.h"



using namespace std;


class QueryProcessor
{
public:
	QueryProcessor();
	~QueryProcessor();
	void parseQuery(std::string);
	void notArgFinder(int);	
	void otherArgFinder(int);
	void stemQuery();
	void print();
private:
	std::string searchQuery;
	std::vector<std::string> searchWords;
	Query* currentQ;
};

#endif 