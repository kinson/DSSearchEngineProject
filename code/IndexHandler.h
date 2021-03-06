/** Index Handler Header File
* Parent function for hashtable and avltree
*Sam Hunter and Morgan Monzingo
*/

#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <iostream>
#include "Page.h"
#include "Query.h"
#include <set>
#include <chrono>

using namespace std;

class IndexHandler
{
public:
	IndexHandler();
	virtual ~IndexHandler();
	virtual std::string getClassType() = 0; //return type of derived class
	void addPage(Page*); //add pages to indexHandler
	virtual void addToIndex(Page*&, std::string&) = 0; //add page to index by keyword
	virtual set<Page*> searchIndex(std::string) = 0; //search index based on keyword
	//set<Page*> compare(set<Page*>, set<Page*>, int); //compare something?
	//set<Page*> readQuery(Query*); //read in user query
	virtual void printTable() = 0;
	//virtual void destroyStructure() = 0; //destructor for data structures

private:


};

#endif
