#include "HashNode.h"

HashNode::HashNode() : Node()
{
  next = nullptr;
}

HashNode* HashNode::getNextHashNode()
{
  return next;
}


void HashNode::setNextHashNode(HashNode* h)
{
  next = h;
}



HashNode::HashNode(Node*& node)
{

}

HashNode::~HashNode(){}
