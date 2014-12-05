#include "Page.h"


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

string Page::getContributingUser()
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

void Page::incrementFreq(int index)
{
  frequency[index]++;
}

//adds the specific keywords for the page object
int Page::addKeyword(string& keyword)
{
  keywords.push_back(keyword);
  frequency.push_back(1);
  return keywords.size()-1;

  //check for duplicate keyword and add to frequency if exists
  /*int index = binarySearch(keywords, keyword, 0, keywords.size());
  if (index == -1)
  {
    frequency.push_back(1);
    keywords.push_back(keyword);
  }
  else
    frequency[index]++;

  sort(keywords.begin(), keywords.end());*/
}

/*void Page::addKeyword(char*& key)
{
  string keyword(key);
  //check for duplicate keyword and add to frequency if exists
  int index = binarySearch(keywords, keyword, 0, keywords.size());
  if (index == -1)
  {
    frequency.push_back(1);
    keywords.push_back(keyword);
  }
  else
    frequency[index]++;
}*/

vector<string> Page::getKeywords()
{
  return keywords;
}

string Page::getKeywordAtIndex(int index)
{
  return keywords[index];
}

int Page::getFrequency(int index)
{
  return frequency[index];
}

int Page::binarySearch(vector<string>& vc, string kw, int low, int high)
{
  if (high - low <= 1)
    return -1;
  int index = (high + low)/2;
  if (kw.compare(vc[index]) == 0)
    return index;
  else if (kw.compare(vc[index]) > 0)
    return binarySearch(vc, kw, index, high);
  else
    return binarySearch(vc, kw, low, index);

}
