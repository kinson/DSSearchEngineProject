#include <iostream>
#include "DocumentParser.h"
#include "IndexHandler.h"
#include "AVLTree.h"

using namespace std;

//main for testing
int main()
{
  DocumentParser* p = new DocumentParser();
  IndexHandler* indexhandler = new AVLTree();
  //p->parseDrive("hugewikibookdump.xml", indexhandler);
  //p->writeToStructure(indexhandler);
  indexhandler->addToIndex(new Page(), "cat");
  indexhandler->printTable();





  return 0;
}
