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


public:
  AVLTree(); //defualt constructor
 ~AVLTree();
  void addToIndex(Page*&, string&); //virtual overridden function
  AVLNode*& insert(string&, Page*&, AVLNode*&);
  AVLNode*& balance(AVLNode*); //manages balancing of tree
  set<Page*> searchIndex(string);
  set<Page*> search(string, AVLNode*&); 

  //functions that deal with and manage height
  int height(AVLNode*); //return height of string
  int difference(AVLNode*); //return difference between left and right subtree height

  //rotations
  AVLNode*& leftRotation(AVLNode*);
  AVLNode*& rightRotation(AVLNode*);
  AVLNode*& doubleLeft(AVLNode*);
  AVLNode*& doubleRight(AVLNode*);

  void printTable();
  void display(AVLNode*, int);
  void inorder(AVLNode*);

  string getClassType(); //return AVLTree
};
#endif
