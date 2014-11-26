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
  //TIMING STUFF
  chrono::time_point<chrono::system_clock> start, end;
  start = chrono::system_clock::now();

  //hash the string
  hash<string> hash_fn;
  size_t hash_val = hash_fn(kw);
  //check the existing hash set
  if ((hashVector[hash_val % hashSize]->getWord() == kw) || (hashVector[hash_val % hashSize]->getWord() == ""))
  {
    //add the page object to the respective page object
    hashVector[hash_val % hashSize]->setWord(kw);
    hashVector[hash_val % hashSize]->addToBinder(pg);
  }
  else
  {
    HashNode* t = hashVector[hash_val % hashSize];
    while (t->getNextHashNode() != nullptr && t->getWord() != kw)
      {
        t = t->getNextHashNode();
      }
      HashNode* newNode = new HashNode();
      newNode->setWord(kw);
      newNode->addToBinder(pg);
      t->setNextHashNode(newNode);
  }

  end = std::chrono::system_clock::now();
  unsigned int milliseconds = chrono::duration_cast<chrono::milliseconds>(end-start).count();
  times.push_back(milliseconds);
}

void HashTable::printTable()
{
  for(HashNode* e: hashVector)
    if (e->getBinder().size() > 0)
      cout << e->getWord() << "\t" << e->getBinder().size() << endl;
}
