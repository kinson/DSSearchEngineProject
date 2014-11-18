#include "DocumentParser.h"



DocumentParser::DocumentParser()
{

}

void DocumentParser::parseDrive(string xmlInFile)
{
  //create ifstream object to read in xmlfile
  ifstream inXMLstream;
  inXMLstream.open(xmlInFile.c_str());
  int counter = 0;
  while(!inXMLstream.eof())
  {
    //read in next word
    string inString;
    inXMLstream >> inString;
    if (inString.compare(0, 5, "<page") == 0)
      cout << "found new page " << counter++ << endl;


  }

}
