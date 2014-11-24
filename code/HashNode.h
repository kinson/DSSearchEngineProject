#ifndef HASHNODE_H
#define HASHNODE_H

#include "Node.h"



class HashNode : public Node
{
friend class HashTable;

private:
  HashNode* next;


public:
  HashNode(); //default constructor
  HashNode( Node*& other); //copy constructor


  //getters
  HashNode* getNextHashNode();

  //setters
  void setNextHashNode(HashNode*);



};

#endif
