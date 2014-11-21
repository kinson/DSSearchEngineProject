#include <iostream>
#include "HashTable.h"
#include <functional>



HashTable::HashTable()
{
  for (size_t i = 0; i < hashSize; i++)
    hashVector.push_back(new HashNode());
}

void HashTable::addToIndex(Page* pg, string kw)
{
  //hash the string
  hash<string> hash_fn;
  size_t hash_val = hash_fn(kw);
  //check the existing hash set (deal with collisions still)
  //add the page object to the respective page object
  hashVector[hash_val % hashSize]->setWord(kw);
  hashVector[hash_val % hashSize]->addToBinder(pg);
}

/*set<Page*> HashTable::searchIndex(string kw)
{

}*/

void HashTable::printTable()
{
  for(auto e: hashVector)
    if (e->getBinder().size() > 0)
      cout << e->getWord() << "\t" << e->getBinder().size() << endl;
}
