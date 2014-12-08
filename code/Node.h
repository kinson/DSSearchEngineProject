/** Node header file
* main data holder for both types of structures
*Sam Hunter and Morgan Monzingo
*/

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

  //getters
  set<Page*> getBinder(); //return binder vector
  string getWord();

  //add to binder
  void addToBinder(Page*&);



};

#endif
