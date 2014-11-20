#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <iostream>

using namespace std;

class HashTable
{
public:
  HashTable(); //default constructor
  void addToIndex(Page*, string); //add an individual word node to the hash table
  set<Page*> searchIndex(string); //search index based on key
  unsigned long hashString(string); //hash a string return an index to place the word in



private:
  vector<Node*> hashVector;
  const unsigned long hashSize;


}


#endif
