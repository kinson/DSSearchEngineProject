/**QueryProcessor header file
*parses through user entered query and saves into query object
* Sam Hunter and Morgan Monzingo
*/


#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Query.h"
#include "IndexHandler.h"
#include "Result.h"
#include "PorterStemmer.h"



using namespace std;


class QueryProcessor
{
public:
	QueryProcessor();
	~QueryProcessor();
	void parseQuery(std::string); // parses by each word
	void notArgFinder(int); //finds all not words
	void otherArgFinder(int); // finds the first set of words
	void stemQuery(); // stems the query
	void print();
	vector<Result*> searchIndex(string, IndexHandler*&); 
	vector<Result*> sortResults(vector<Page*>&); //sort results vectors
	vector<Result*> merge_sort(vector<Result*>& vec); //merge sort for result vector
	vector<Result*> merge(vector<Result*>&,const vector<Result*>&, const vector<Result*>&);

private:
	std::string searchQuery;
	std::vector<std::string> searchWords;
	Query* currentQ;
};

#endif
