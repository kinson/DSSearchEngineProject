#include "AVLNode.h"

AVLNode::AVLNode() : Node(nullptr, "")
{
  right = nullptr;
  left = nullptr;
}

AVLNode::AVLNode(string kw, Page* pg) : Node(pg, kw)
{
  right = nullptr;
  left = nullptr;
}

AVLNode::AVLNode(string kw, AVLNode*& rightnode, AVLNode*& leftnode, Page* pg) : Node(pg, kw)
{
  right = rightnode;
  left = leftnode;
}


/*bool operator<(AVLNode& left, string& kw)
{
  cout << "using custom comparison" << endl;
  return (kw.compare(left.getWord()) < 0);
}

bool operator>(AVLNode& left, string& kw)
{
  cout << "using custom comparison" << endl;
  return (kw.compare(left.getWord()) > 0);
}*/
