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
  //check the existing hash set
  if (hashVector[hash_val % hashSize]->getWord() != kw && hashVector[hash_val % hashSize]->getWord() != "")
  {
    HashNode t = HashNode(hashVector[hash_val % hashSize]);
    HashNode* p = &t;
    while (p->getNextHashNode() != nullptr && p->getWord() != kw)
    {
      p = p->getNextHashNode();
    }
    HashNode* newNode = new HashNode();
    newNode->setWord(kw);
    newNode->addToBinder(pg);
    p->setNextHashNode(newNode);
  }
  else
  {
    //add the page object to the respective page object
    hashVector[hash_val % hashSize]->setWord(kw);
    hashVector[hash_val % hashSize]->addToBinder(pg);
  }
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
