#include "Page.h"


using namespace std;
Page::Page()
{
  fullText = "";
}

//getters and setters for Page
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

}

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

void Page::setFrequency(int index, int freq)
{
  frequency[index] = freq;
}

void Page::setFullText(string text)
{
  fullText = text;
}

string Page::getFullText()
{
  return fullText;
}
