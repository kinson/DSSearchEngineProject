#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <set>
#include "Page.h"

using namespace std;

class Node
{
private:
  string word;
  set<Page*> binder;




public:
  Node(Page*, string); //constructor for node
  Node();
  string getName(); //return string of keyword
  set<Page*> getSetOfPages(); //return set of pages for a certain keyword

  //setters
  void setWord(string);

  //add to binder
  void addToBinder(Page*&);



};

#endif
