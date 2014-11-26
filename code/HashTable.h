#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <set>
#include <iostream>
#include "Page.h"
#include "Node.h"
#include "HashNode.h"
#include "IndexHandler.h"


using namespace std;

class HashTable: public IndexHandler
{
public:
  HashTable(); //default constructor
  void addToIndex(Page*&, string&); //add an individual word node to the hash table
  //set<Page*> searchIndex(string); //search index based on key
  //unsigned long hashString(string); //hash a string return an index to place the word in
  void printTable(); //print out hashtable
  set<Page*> searchIndex(string);


private:
  vector<HashNode*> hashVector;
  const unsigned long hashSize =  1000000;


};


#endif
