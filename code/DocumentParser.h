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
//#include "PorterStemmer.h"



using namespace std;

class DocumentParser
{

public:
  DocumentParser(); //constructor for doc parser
  void parseDrive(string, IndexHandler*&); //open file and parse the xml file
  void sendToIndex(Page*); //send an individual page index
  void writeToStructure(IndexHandler*&, int startIndex = 0); //iterate over collection, sending it to the index
  void saveIndex();
  void readInParsedFile(IndexHandler*&); //function to read in an already parsed file
  int getCollectionSize();


private:
  vector<Page*> collection;
  map<string, bool> stopwords;
  vector<string> throwout;


};

#endif
