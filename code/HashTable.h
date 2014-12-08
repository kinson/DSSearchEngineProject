/** Hash table header file
* virtual function, parent is index handler
* hash table structure object
* Sam Hunter and Morgan Monzingo
*/

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
  ~HashTable();
  void addToIndex(Page*&, std::string&); //add an individual word node to the hash table
  void printTable(); //print out hashtable
  set<Page*> searchIndex(std::string);
  void saveIndex(); //save index in offline file
  std::string getClassType(); //return HashTable

private:
  vector<HashNode*> hashVector;
  const unsigned long hashSize =  1000000;


};


#endif
