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

//adds the specific keywords for the page object
void Page::addKeyword(string& keyword)
{
  //check for duplicate keyword and add to frequency if exists
  int index = binarySearch(keywords, keyword, 0, keywords.size());
  if (index == -1)
  {
    frequency.push_back(1);
    keywords.push_back(keyword);
  }
  else
    frequency[index]++;
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

int Page::binarySearch(vector<string>& vc, string kw, int low, int high)
{

  if (high - low <= 1)
    return -1;
  int index = (high + low)/2;
  //cout << "high\t" << high << "index\t" << index << "low\t" << low << endl;
  if (kw.compare(vc[index]) == 0)
    return index;
  else if (kw.compare(vc[index]) > 0)
    return binarySearch(vc, kw, index, high);
  else
    return binarySearch(vc, kw, low, index);

}
