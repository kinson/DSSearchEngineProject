#include <fstream>
#include <iostream>

#include "DocumentParser.h"
#include "IndexHandler.h"
#include "AVLTree.h"
#include "UserInterface.h"
#include <iomanip>
//#include "Page.h"
#include "QueryProcessor.h"
using namespace std;


int main()
{

  //declare and instantiate user interface
  UserInterface* ui = new UserInterface();
  ui->driver();

  //DocumentParser* p = new DocumentParser();
  //IndexHandler* indexhandler = new HashTable();
  //p->parseDrive("hugewikibookdump.xml", indexhandler);
  //p->saveIndex();
  //p->writeToStructure(indexhandler);
  //indexhandler->addToIndex(new Page(), "cat");
  //p->readInParsedFile(indexhandler);
  //set<Page*> results = indexhandler->searchIndex("ffded");





  return 0;
}






//main for testing
/*int main()
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
}*/
