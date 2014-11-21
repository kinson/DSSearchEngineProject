#include "Node.h"

Node::Node()
{
}

Node::Node(Page* pg, string keyword)
{
  //binder.

}

void Node::setWord(string newword)
{
  word = newword;
}

void Node::addToBinder(Page*& pg)
{
  binder.insert(pg);
}
