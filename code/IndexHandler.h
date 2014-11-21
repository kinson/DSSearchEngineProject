#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <iostream>
#include "Page.h"
#include "Query.h"
#include <set>
using namespace std;

class IndexHandler
{
public:
	IndexHandler();
	void addPage(Page*); //add pages to indexHandler
	virtual void addToIndex(Page*, string) = 0; //add page to index by keyword
	//virtual set<Page*> searchIndex(string); //search index based on keyword
	//set<Page*> compare(set<Page*>, set<Page*>, int); //compare something?
	//set<Page*> readQuery(Query*); //read in user query
	virtual void printTable() = 0;


private:

};

#endif
