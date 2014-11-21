#include "Node.h"

Node::Node()
{
}

Node::Node(Page* pg, string keyword)
{

}

void Node::setWord(string newword)
{
  word = newword;
}

void Node::addToBinder(Page*& pg)
{
  binder.insert(pg);
}

set<Page*> Node::getBinder()
{
  return binder;
}

string Node::getWord()
{
  return word;
}
