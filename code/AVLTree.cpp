#include "AVLTree.h"


AVLTree::AVLTree()
{
  root = nullptr;
  depth = 0;
}

void AVLTree::addToIndex(Page* pg, string kw)
{
  insert(kw, pg, root, root);

}

void AVLTree::insert(string kw, Page* pg, AVLNode*& avlnode, AVLNode*& parent)
{
  if (avlnode == nullptr)
  {
    //parent points to iteself for the root
    avlnode = new AVLNode(kw, pg, parent);
    avlnode->depth = parent->depth + 1;
  }
  else if (avlnode->getWord() < kw)
    return insert(kw, pg, avlnode->right, avlnode);
  else
    return insert(kw, pg, avlnode->left, avlnode);

}

bool AVLTree::balance(AVLNode*& avlnode)
{
  if (avlnode->left != nullptr)
    return balance(avlnode->left);
  else if (avlnode->right != nullptr)
    return balance(avlnode->right);

  cout << avlnode->getWord() << endl;
  if (abs(avlnode->left->depth - avlnode->right->depth) == 2)
  {
    balanceTree(avlnode);
    return false;
  }
  return true;
}

void AVLTree::balanceTree(AVLNode*& alpha)
{



}

void AVLTree::printTable()
{
  cout << "here 4 u" << endl;
}
