#ifndef AVLNODE_H
#define AVLNODE_H

#include <iostream>
#include "Node.h"
#include "Page.h"


class AVLNode : public Node
{
friend class AVLTree;

private:
  AVLNode* left;
  AVLNode* right;


public:
  //constructors
  AVLNode();
  AVLNode(string, Page*);
  AVLNode(string, AVLNode*&, AVLNode*&, Page*);


  //override comparison constructors for string comparing
  //friend bool operator<(AVLNode&, string&);
  //friend bool operator>(AVLNode&, string&);




};
#endif
