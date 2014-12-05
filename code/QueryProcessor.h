#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Query.h"
#include "IndexHandler.h"
//#include "PorterStemmer.h"



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
	vector<Page*> searchIndex(string, IndexHandler*&);
	void sortResults(vector<Page*>&); //sort results vectors
private:
	std::string searchQuery;
	std::vector<std::string> searchWords;
	Query* currentQ;
};

#endif
