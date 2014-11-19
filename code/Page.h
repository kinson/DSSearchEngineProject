#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <vector>
#include "porter2_stemmer.h"

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

  //getters
  string getTitle();
  unsigned long getId();
  string getContriutingUser();
  string getDate();
  vector<string> getKeywords();

  void addKeyword(string); //add to keyword vector

  ~Page(); //destructor for page object



private:
  string title;
  unsigned long id;
  string contributingUser;
  string date;
  vector<string> keywords;
  vector<int> frequency;

};

#endif
