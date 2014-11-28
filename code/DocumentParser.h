#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <fstream>
#include <vector>
#include "Page.h"
#include "IndexHandler.h"
#include "HashTable.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <cctype>

using namespace std;

class DocumentParser
{

public:
  DocumentParser(); //constructor for doc parser
  void parseDrive(string, IndexHandler*&); //open file and parse the xml file
  void sendToIndex(Page*); //send an individual page index
  void writeToStructure(IndexHandler*&); //iterate over collection, sending it to the index
  void saveIndex();
  void readInParsedFile(IndexHandler*&); //function to read in an already parsed file


private:
  vector<Page*> collection;
  map<string, bool> stopwords;
  vector<string> throwout;


};

#endif
