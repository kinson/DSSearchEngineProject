#include "AVLNode.h"

AVLNode::AVLNode() : Node(nullptr, "")
{
  right = nullptr;
  left = nullptr;
  depth = -1;
}

AVLNode::AVLNode(string kw, Page* pg) : Node(pg, kw)
{
  right = nullptr;
  left = nullptr;
  depth = -1;
}

AVLNode::AVLNode(string kw, AVLNode*& rightnode, AVLNode*& leftnode, Page* pg) : Node(pg, kw)
{
  right = rightnode;
  left = leftnode;
  depth = -1;
}

AVLNode::AVLNode(string kw, Page* pg, AVLNode*& parentnode) : Node(pg, kw)
{
  right = nullptr;
  left = nullptr;
  depth = -1;
  parent = parentnode;
}

bool operator<(AVLNode& left, string& kw)
{
  return (kw.compare(left.getWord()) < 0);
}

bool operator>(AVLNode& left, string& kw)
{
  return (kw.compare(left.getWord()) > 0);
}