#include <iostream>
#include "HashTable.h"
#include <functional>


HashTable::HashTable()
{
  for (size_t i = 0; i < hashSize; i++)
    hashVector.push_back(new HashNode());
}

void HashTable::addToIndex(Page*& pg, string& kw)
{

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

}

void HashTable::printTable()
{
  for(HashNode* e: hashVector)
    if (e->getBinder().size() > 0)
      cout << e->getWord() << "\t" << e->getBinder().size() << endl;
}


set<Page*> HashTable::searchIndex(string search_term)
{
  hash<string> hash_fn;
  size_t hash_val = hash_fn(search_term);
  HashNode* t = hashVector[hash_val % hashSize];
  while (t->getNextHashNode() != nullptr && t->getWord() != search_term)
    t = t->getNextHashNode();
  return t->getBinder();

}


string HashTable::getClassType()
{
  return "HashTable";
}


HashTable::~HashTable()
{
  cout << "Bitches aint shit" << endl;
  for(int i = 0; i < hashVector.size(); i++)
    delete[] hashVector[i];
}
