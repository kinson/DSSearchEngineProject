#ifndef NODE_H
#define NODE_H



#include <iostream>
#include <set>

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




}
