
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

AVLNode::~AVLNode()
{
  delete right; delete left;
}

