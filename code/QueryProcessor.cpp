#include "QueryProcessor.h"
#include "stemHelper.h"



QueryProcessor::QueryProcessor()
{
  currentQ = new Query;
}

QueryProcessor::~QueryProcessor()
{

}

void QueryProcessor::parseQuery(std::string search)
{
  if(currentQ->getandArgs().size()!=0||currentQ->getorArgs().size()!=0||currentQ->getnotArgs().size()!=0||currentQ->getnormArgs().size()!=0)
    currentQ->clearQuery();
  searchQuery = search;
	istringstream inString(searchQuery);
	cout << searchQuery << endl;

  //reading in the query by word save into vector
  while (inString)
  {
    string temp;
    //breaks if there aren't any words left
    if (!getline(inString, temp, ' '))
      break;
    //otherwise adds to the search words vector
    searchWords.push_back(temp);
  }

  //finds if there are any not keywords in the file
  for(int i = searchWords.size() - 1; i >= 0 ; i--)
  {
    //adds to not vector if the keyword is found
    if(searchWords[i].compare("NOT")==0)
    {
      notArgFinder(i);
      break;
    }
  }

  if(searchWords[0].compare("AND")==0)
    otherArgFinder(0);
  if(searchWords[0].compare("OR")==0)
    otherArgFinder(1);
  else
    otherArgFinder(2);

  stemQuery();

}

void QueryProcessor::stemQuery()
{
  char* buffer;
  for(int i = 0; i < currentQ->getandArgs().size(); i++)
  {
    buffer = (char*) currentQ->getandArgs(i).c_str();
    string newString = StemHelper::stemword(buffer);
    currentQ->setandArgs(i, buffer);

  }

  for(int i = 0; i < currentQ->getorArgs().size(); i++)
  {
    buffer = (char*) currentQ->getorArgs(i).c_str();
    string newString = StemHelper::stemword(buffer);
    currentQ->setorArgs(i, buffer);

  }

    for(int i = 0; i < currentQ->getnotArgs().size(); i++)
  {
    buffer = (char*) currentQ->getnotArgs(i).c_str();
    string newString = StemHelper::stemword(buffer);
    currentQ->setnotArgs(i, buffer);

  }

   for(int i = 0; i < currentQ->getnormArgs().size(); i++)
  {
    buffer = (char*) currentQ->getnormArgs(i).c_str();
    string newString = StemHelper::stemword(buffer);
    currentQ->setnormArgs(i, buffer);

  }

}

void QueryProcessor::notArgFinder(int loc)
{
  int size = searchWords.size();
  for(int i = loc + 1; i < size; i++)
  {
    transform(searchWords[i].begin(), searchWords[i].end(), searchWords[i].begin(), ::tolower);
    currentQ->addnotArgs(searchWords[i]);
  }

  searchWords.erase(searchWords.begin()+loc, searchWords.begin()+size);
}

void QueryProcessor::otherArgFinder(int type)
{
  switch (type)
  {
    case 0:
        {
        for(int i = 1; i < searchWords.size(); i++)
        {
          transform(searchWords[i].begin(), searchWords[i].end(), searchWords[i].begin(), ::tolower);
          currentQ->addandArgs(searchWords[i]);
        }
        break;
        }
    case 1:
      {
        for(int i = 1; i < searchWords.size(); i++)
        {
          transform(searchWords[i].begin(), searchWords[i].end(), searchWords[i].begin(), ::tolower);
          currentQ->addandArgs(searchWords[i]);
        }
        break;
      }
    case 2:
      {
        for(int i = 0; i < searchWords.size(); i++)
        {
          transform(searchWords[i].begin(), searchWords[i].end(), searchWords[i].begin(), ::tolower);
          currentQ->addandArgs(searchWords[i]);
        }
        break;
      }
    }
}

void QueryProcessor::print()
{
  currentQ->printQuery();
}
