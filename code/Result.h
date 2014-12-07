#ifndef RESULT_H
#define RESULT_H

#include <iostream>

using namespace std;

class Result
{
private:
  Page* infoPage;
  string fullText;
  double inverseFrequencyValue;


public:
  Result()
  {}
  Result(Page* info, double invFreq) //double argument constructor
  {
    infoPage = info;
    inverseFrequencyValue = invFreq;
    fullText = "";
  }
  Result(Page* info, double invFreq, string full) : Result(info, invFreq)
  {
    fullText = full;
  }

  void addFullText(string text)
  {
    fullText = text;
  }

  int getId()
  {
    if (infoPage != nullptr)
      return infoPage->getId();
    return -1; //no page set
  }

  string getTitle()
  {
    if (infoPage != nullptr)
      return infoPage->getTitle();
    return "";
  }

  Page* getPage()
  {
    return infoPage;
  }

  double getInverseFrequency()
  {
    return inverseFrequencyValue;
  }

  string getFullText()
  {
    return infoPage->fullText;
  }

  string getDate()
  {
    return infoPage->getDate();
  }
};
#endif
