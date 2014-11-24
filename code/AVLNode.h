#ifndef AVLNODE_H
#define AVLNODE_H

#include <iostream>
#include "Node.h"
#include "Page.h"


class AVLNode : public Node
{
friend class AVLTree;

private:
  int depth;
  AVLNode* left;
  AVLNode* right;
  AVLNode* parent;



public:
  //constructors
  AVLNode(string, Page*);
  AVLNode(string, Page*, AVLNode*&); //constructor with parent node
  AVLNode();
  AVLNode(string, AVLNode*&, AVLNode*&, Page*);


  //override comparison constructors for string comparing
  friend bool operator<(AVLNode&, string&);
  friend bool operator>(AVLNode&, string&);




};
#endif
