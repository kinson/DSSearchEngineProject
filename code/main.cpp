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
  p->parseDrive("hugewikibookdump.xml", indexhandler);
  //p->writeToStructure(indexhandler);
  //indexhandler->addToIndex(new Page(), "cat");
  //indexhandler->printTable();
  set<Page*> results = indexhandler->searchIndex("ffded");
  cout << results.size() << endl;
  for (auto e: results)
    cout << e->getTitle() << endl;



  return 0;
}
