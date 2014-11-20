#include "Page.h"
#include <iostream>
#include <vector>

using namespace std;
Page::Page()
{}

void Page::setTitle(string t)
{
  title = t;
}

string Page::getTitle()
{
  return title;
}

void Page::setId(unsigned long num)
{
  id = num;
}

unsigned long Page::getId()
{
  return id;
}

void Page::setContributingUser(string username)
{
  contributingUser = username;
}

string getContributingUser()
{
  return contributingUser;
}


void Page::setDate(string d)
{
  date = d;
}

string Page:: getDate()
{
  return date;
}

//adds the specific keywords for the page object
void Page::addKeyword(string keyword)
{
  //check for duplicate keyword and add to frequency if exists
  for(size_t i = 0; i < keywords.size(); i++)
  {
    if (keywords[i].compare(keyword) == 0)
    {
      frequency[i] += 1;
      return;
    }
  }
  //add new keyword
  keywords.push_back(keyword);
  frequency.push_back(1);
}

vector<string> Page::getKeywords()
{
  return keywords;
}
