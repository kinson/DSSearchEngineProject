#include <fstream>
#include <iostream>
#include "DocumentParser.h"
#include "IndexHandler.h"
#include "AVLTree.h"
#include <iomanip>
#include "Page.h"

using namespace std;


//main for testing
int main()
{
  DocumentParser* p = new DocumentParser();
  IndexHandler* indexhandler = new HashTable();
  //p->parseDrive("hugewikibookdump.xml", indexhandler);
  //p->saveIndex();
  //p->writeToStructure(indexhandler);
  //indexhandler->addToIndex(new Page(), "cat");
  p->readInParsedFile(indexhandler);
  //set<Page*> results = indexhandler->searchIndex("ffded");
  return 0;
}
