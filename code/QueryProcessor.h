#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <vector>
#include <string>
#include <sstream> 
#include <iostream>
#include "Query.h"
#include "PorterStemmer.h"


using namespace std;


class QueryProcessor
{
public:
	QueryProcessor();
	~QueryProcessor();
	void parseQuery(std::string);
	std::string stemQuery(std::string&, stemmer*);
	void notArgFinder(int, stemmer*);	
	void otherArgFinder(int, stemmer*);
	void print();
private:
	std::string searchQuery;
	std::vector<std::string> searchWords;
	Query* currentQ;
};

#endif 