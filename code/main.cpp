
#include <iostream>
#include "DocumentParser.h"

using namespace std;

//main for testing
int main()
{
  DocumentParser* p = new DocumentParser();
  p->parseDrive("hugewikibookdump.xml");
  //p->writeToStructure();




  return 0;
}
