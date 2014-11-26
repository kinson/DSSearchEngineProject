#include <fstream>
#include <iostream>
#include "DocumentParser.h"
#include "IndexHandler.h"
#include "AVLTree.h"
#include <iomanip>
#include <thread>
#include <chrono>


using namespace std;



void write(DocumentParser*& p, IndexHandler*& ih)
{
  this_thread::sleep_for(chrono::milliseconds(4800));
  p->writeToStructure(ih);
}


//main for testing
int main()
{
  DocumentParser* p = new DocumentParser();
  IndexHandler* indexhandler = new AVLTree();
  thread t1(write, ref(p), ref(indexhandler));
  p->parseDrive("hugewikibookdump.xml", indexhandler);
  //p->writeToStructure(indexhandler);
  t1.join();
  //indexhandler->addToIndex(new Page(), "cat");
  //indexhandler->printTable();



  return 0;
}
