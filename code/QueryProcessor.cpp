#include "QueryProcessor.h"

QueryProcessor::QueryProcessor()
{
  Query* currentQ = new Query;
}

QueryProcessor::~QueryProcessor()
{

}

void QueryProcessor::parseQuery(std::string search)
{
	searchQuery = search;
	istringstream inString(searchQuery);
	cout << searchQuery << endl;

  //reading in the query by word save into vector
  while (inString)
  {
    string temp;
    if (!getline( inString, temp, ' ' )) 
      break;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    searchWords.push_back( temp );
  }
  for(int i = searchWords.size() - 1; i >= 0 ; i--)
  {
    if(searchWords[i].compare("not")==0)
    {
      notArgFinder(i);
      break;
    } 
  }

  if(searchWords[0].compare("and")==0)
    otherArgFinder(0);
  if(searchWords[0].compare("or")==0)  
    otherArgFinder(1);
  else
    otherArgFinder(2);

}

void QueryProcessor::notArgFinder(int loc)
{
  int size = searchWords.size();
  for(int i = loc; i < size; i++)
  {
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
          currentQ->addandArgs(searchWords[i]); 
        }
        break;
        }
    case 1:
      {
        for(int i = 1; i < searchWords.size(); i++)
        {
          currentQ->addorArgs(searchWords[i]);
        }
        break;
      }
    case 2:
      {
        for(int i = 0; i < searchWords.size(); i++)
        {
            currentQ->addnormArgs(searchWords[i]);
        }
        break;
      } 
    }
}




















