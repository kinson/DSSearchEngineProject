#include "AVLTree.h"


AVLTree::AVLTree()
{
  root = nullptr;
  depth = 0;
}

void AVLTree::addToIndex(Page* pg, string kw)
{
  vector<string>tests = {"three", "two", "cat", "dog"};
  for (auto e: tests)
    insert(e, pg, root, root);
  //balance(root);
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
  cout << "here" << endl;
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
  if (alpha->left != nullptr && alpha->right == nullptr)
  {
    if (alpha->left->left != nullptr && alpha->left->right)
      cout << "double right" << endl; //rightRotation(alpha);
    else
      cout << "doubleRight" << endl; //doubleRight(alpha);
  }
  else if (alpha->right != nullptr && alpha->left == nullptr)
  {
    if (alpha->right->right != nullptr && alpha->right->left == nullptr)
      cout << "leftRotation" << endl; //leftRotation(alpha);
    else
      cout << "doubleLeft" << endl; //doubleLeft(alpha);
  }
}


void AVLTree::rightRotation(AVLNode*& alpha)
{
  if (alpha->parent->left == alpha)
  {
    alpha->parent->left = alpha->left;
    alpha->left->parent = alpha->parent;
  }
  else if( alpha->parent->right == alpha)
  {
    alpha->parent->right = alpha->left;
    alpha->left->parent = alpha->parent;
  }
  else
    cout << "this aint gonna work" << endl;
  alpha->left = alpha->left->right;
  alpha->left->right = alpha;
  alpha->parent = alpha->left;
}

void AVLTree::print(AVLNode*& node)
{
  cout << node->getWord() << endl;
  if (node->left != nullptr)
    return print(node->left);
  if (node->right != nullptr)
    return print(node->right);

    return;
}

void AVLTree::printTable()
{
  print(root);
}
