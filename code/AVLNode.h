
/** AVL Node header file
* Sam Hunter and Morgan Monzingo
* node built for AVL tree 
*/
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
  ~AVLNode();





};
#endif
