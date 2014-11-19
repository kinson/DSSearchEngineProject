#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <vector>

using namespace std;

class Page
{
public:
  Page(); //constructor for page

  //setters
  void setTitle(string);
  void setId(unsigned long);
  void setContributingUser(string);

  //getters
  string getTitle();
  unsigned long getId();
  string getContriutingUser();

  void addKeyword(string); //add to keyword vector



private:
  string title;
  unsigned long id;
  string contributingUser;
  vector<string> keywords;
  vector<int> frequency;

};

#endif
