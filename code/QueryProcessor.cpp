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
  struct stemmer* stm = create_stemmer();
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
      notArgFinder(i, stm);
      break;
    } 
  }

  if(searchWords[0].compare("and")==0)
    otherArgFinder(0, stm);
  if(searchWords[0].compare("or")==0)  
    otherArgFinder(1, stm);
  else
    otherArgFinder(2, stm);

}

std::string QueryProcessor::stemQuery(std::string& qWord, stemmer*stm)
{

  char* buffer = (char*) qWord.c_str();
  int stringEnd = stem(stm, buffer, qWord.length()-1);
  buffer[stringEnd +1] = '\0';
  string stemWord = bufffer;
  return stemWord;
}

void QueryProcessor::notArgFinder(int loc, stemmer* stm)
{
  string queryKeyword;
  int size = searchWords.size();
  for(int i = loc; i < size; i++)
  {
    queryKeyword = stemQuery(searchWords[i], stm);
    currentQ->addnotArgs(queryKeyword);
  }
  searchWords.erase(searchWords.begin()+loc, searchWords.begin()+size);
}

void QueryProcessor::otherArgFinder(int type, stemmer* stm)
{
  string queryKeyword;
  switch (type)
  {
    case 0:
        {
        for(int i = 1; i < searchWords.size(); i++)
        {
          queryKeyword = stemQuery(searchWords[i], stm);
          currentQ->addandArgs(queryKeyword); 
        }
        break;
        }
    case 1:
      {
        for(int i = 1; i < searchWords.size(); i++)
        {
          queryKeyword = stemQuery(searchWords[i], stm);
          currentQ->addandArgs(queryKeyword); 
        }
        break;
      }
    case 2:
      {
        for(int i = 0; i < searchWords.size(); i++)
        {
          queryKeyword = stemQuery(searchWords[i], stm);
          currentQ->addandArgs(queryKeyword); 
        }
        break;
      } 
    }
}

void QueryProcessor::print()
{
  currentQ->printQuery();
}




















