#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include "IndexHandler.h"
#include "AVLNode.h"
#include <cmath>

using namespace std;

class AVLTree : public IndexHandler
{
friend class AVLNode;

private:
  AVLNode* root;
  int depth;


public:
  AVLTree(); //defualt constructor
  void addToIndex(Page*, string); //virtual overridden function
  void insert(string, Page*, AVLNode*&, AVLNode*&);
  bool balance(AVLNode*&);
  void balanceTree(AVLNode*&);

  void printTable();
  void print(AVLNode*&); //override pvf from indexhandler

  void rightRotation(AVLNode*&);

};
#endif
