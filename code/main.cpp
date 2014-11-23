
#include <iostream>
#include "DocumentParser.h"
#include "IndexHandler.h"

using namespace std;

//main for testing
int main()
{
  DocumentParser* p = new DocumentParser();
  p->parseDrive("hugewikibookdump.xml");
  IndexHandler* indexhandler = new HashTable();
  p->writeToStructure(indexhandler);
  indexhandler->printTable();




  return 0;
}
