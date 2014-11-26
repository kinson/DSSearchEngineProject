#include "AVLTree.h"

/**********************************************************************************************************************
                      PSEUDO CODE FOUND AT  http://www.sanfoundry.com/cpp-program-implement-avl-trees/
**********************************************************************************************************************/

AVLTree::AVLTree()
{
  root = nullptr;
}

void AVLTree::addToIndex(Page* pg, string kw)
{
  chrono::time_point<chrono::system_clock> start, end;
  start = chrono::system_clock::now();
  /*vector<string>tests = {"three", "two", "cat", "dog", "date", "zebra", "elephant", "turd", "faith", "cat", "fun", "alpha", "jack"};
  for (auto e: tests)
    insert(e, pg, root);*/
  insert(kw, pg, root);

  end = std::chrono::system_clock::now();
  unsigned int milliseconds = chrono::duration_cast<chrono::milliseconds>(end-start).count();
  times.push_back(milliseconds);
}

AVLNode*& AVLTree::insert(string& kw, Page*& pg, AVLNode*& avlnode)
{
  if (this->root == nullptr)
  {
    this->root = new AVLNode(kw, pg);
  }
  else if (avlnode == nullptr)
  {
    avlnode = new AVLNode(kw, pg);
  }
  //handle duplicated, add page to existing AVLNode binder
  else if (avlnode->getWord() == kw)
  {
    avlnode->addToBinder(pg);
  }
  else if (avlnode->getWord() < kw)
  {
    insert(kw, pg, avlnode->right);
    avlnode = balance(avlnode);
  }
  else
  {
    insert(kw, pg, avlnode->left);
    avlnode = balance(avlnode);
  }
  return avlnode;

}

AVLNode*& AVLTree::leftRotation(AVLNode*& avlnode)
{
  AVLNode* temp;
  temp = avlnode->left;
  avlnode->left = temp->right;
  temp->right = avlnode;
  return temp;
}

AVLNode*& AVLTree::rightRotation(AVLNode*& avlnode)
{
  AVLNode* temp;
  temp = avlnode->right;
  avlnode->right = temp->left;
  temp->left = avlnode;
  return temp;
}

AVLNode*& AVLTree::doubleLeft(AVLNode*& avlnode)
{
  AVLNode* temp;
  temp = avlnode->left;
  avlnode->left = rightRotation(temp);
  return leftRotation(avlnode);
}

AVLNode*& AVLTree::doubleRight(AVLNode*& avlnode)
{
  AVLNode* temp;
  temp = avlnode->right;
  avlnode->right = leftRotation(temp);
  return rightRotation(avlnode);
}


AVLNode*& AVLTree::balance(AVLNode*& avlnode)
{
  int bal = difference(avlnode);
  if (bal > 1)
  {
    if (difference(avlnode->left) > 0)
      avlnode = leftRotation(avlnode);
    else
      avlnode = doubleLeft(avlnode);
  }
  else if(bal < -1)
  {
    if (difference(avlnode->right) > 0)
      avlnode = doubleRight(avlnode);
    else
      avlnode = rightRotation(avlnode);
  }
  return avlnode;

}

int AVLTree::height(AVLNode* avlnode)
{
  int h = 0;
  if (avlnode != nullptr)
  {
    int leftHeight = height(avlnode->left);
    int rightHeight = height(avlnode->right);
    int max_height = max(rightHeight, leftHeight);
    h = max_height + 1;
  }
  return h;
}

int AVLTree::difference(AVLNode* avlnode)
{
  int l = height(avlnode->left);
  int r = height(avlnode->right);
  int diff = l - r;
  return diff;
}

void AVLTree::printTable()
{
  inorder(root);
}


void AVLTree::display(AVLNode* avlnode, int level)
{
  int i;
  if(avlnode != nullptr)
  {
    display(avlnode->right, level + 1);
    printf("\n");
    if (avlnode == root) cout << "Root -> ";
    for (int i = 0; i < level  && avlnode != root; i++)
    {
      cout << "            " << endl;
    }
    cout << avlnode->getWord();
    display(avlnode->left, level + 1);
  }
}


void AVLTree::inorder(AVLNode* temp)
{
  if (temp == nullptr)
    return;
  inorder(temp->left);
  cout << temp->getWord() << " " << temp->getBinder().size() << "\t";
  inorder(temp->right);
}
