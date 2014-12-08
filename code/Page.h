/** Page header file 
* object that holds all information for each xml file
*Sam Hunter and Morgan Monzingo
*/

#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <vector>
#include <string>
//#include "porter2_stemmer.h"

using namespace std;

class Page
{
public:
  Page(); //constructor for page

  //setters
  void setTitle(string);
  void setId(unsigned long);
  void setContributingUser(string);
  void setDate(string);
  void setFrequency(int, int);
  void setFullText(string);
  string getFullText();

  //getters
  string getTitle();
  unsigned long getId();
  string getContributingUser();
  string getDate();
  vector<string> getKeywords();
  int getFrequency(int); //return frequency of word at index
  string getKeywordAtIndex(int);
  void incrementFreq(int); //increment the frequency of given word

  int addKeyword(string&); //add to keyword vector

  ~Page(); //destructor for page object

  static int binarySearch(vector<string>&, string, int, int); //search over a vector, return true if the string exists

  string fullText;



private:
  string title;
  unsigned long id;
  string contributingUser;
  string date;
  vector<string> keywords;
  vector<int> frequency;

};

#endif
