#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Page.h"
#include <algorithm>

using namespace std;

class DocumentParser
{
public:
  DocumentParser(); //constructor for doc parser
  void parseDrive(string); //open file and parse the xml file
  Page* findPage(); //what does this do?
  void parsePage(); //again ???
  void sendToIndex(Page*); //send an individual page index
  void writeToStructure(); //not really sure about this either




private:
  vector<Page*> collection;
  vector<string> stopwords;
  vector<string> throwout;

};

#endif
