#include "Page.h"


Page::Page()
{}


void Page::addKeyword(string keyword)
{
  for(size_t i = 0; i < keywords.size(); i++)
  {
    if (keywords[i].compare(keyword) == 0)
    {
      frequency[i] += 1;
      return;
    }
  }
  keywords.push_back(keyword);
  frequency.push_back(1);
}

vector<string> Page::getKeywords()
{
  return keywords;
}
