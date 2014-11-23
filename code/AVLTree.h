#ifndef AVLTree
#define AVLTree

#include "IndexHandler.h"
#include "AVLNode.h"

class AVLTree : public IndexHandler
{
private:
  AVLNode* root;
  int depth;


public:
  AVLTree(); //defualt constructor
  void addToIndex(Page*, string); //virtual overridden function



};
