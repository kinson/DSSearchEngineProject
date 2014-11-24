#include <iostream>
#include "DocumentParser.h"
#include "IndexHandler.h"
#include "AVLTree.h"

using namespace std;

//main for testing
int main()
{
  DocumentParser* p = new DocumentParser();
  IndexHandler* indexhandler = new HashTable();
  p->parseDrive("hugewikibookdump.xml", indexhandler);
  p->writeToStructure(indexhandler);
  indexhandler->printTable();





  return 0;
}
