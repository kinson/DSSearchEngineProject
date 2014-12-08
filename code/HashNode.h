/** Hash node header file
* Sam Hunter and Morgan Monzingo
*/

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
  HashNode(Node*& other); //copy constructor
  ~HashNode();


  //getters
  HashNode* getNextHashNode();

  //setters
  void setNextHashNode(HashNode*);



};

#endif
