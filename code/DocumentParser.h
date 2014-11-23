#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <fstream>
#include <vector>
#include "Page.h"
#include "IndexHandler.h"
#include "HashTable.h"
#include <algorithm>
#include <sstream>
#include <map>
#include <iostream>
//#include "english_stem.h"

using namespace std;

class DocumentParser
{

public:
  DocumentParser(); //constructor for doc parser
  void parseDrive(string); //open file and parse the xml file
  void sendToIndex(Page*); //send an individual page index
  void writeToStructure(IndexHandler*&); //iterate over collection, sending it to the index


private:
  vector<Page*> collection;
  map<string, bool> stopwords;
  vector<string> throwout;


};

#endif
