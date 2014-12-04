#include "QueryProcessor.h"
#include "stemHelper.h"



QueryProcessor::QueryProcessor()
{
  currentQ = new Query();
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
    //breaks if there aren't any words left
    if (!getline(inString, temp, ' '))
      break;
    //otherwise adds to the search words vector
    searchWords.push_back(temp);
  }
  currentQ->clearQuery();
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
  else
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
        cout << "maybe here " <<  searchWords.size() << endl;
        for(int i = 1; i < searchWords.size(); i++)
        {
          transform(searchWords[i].begin(), searchWords[i].end(), searchWords[i].begin(), ::tolower);
          cout << "made it here with " << searchWords[i] << endl;
          currentQ->addandArgs(searchWords[i]);
        }
        break;
        }
    case 1:
      {
        for(int i = 1; i < searchWords.size(); i++)
        {
          transform(searchWords[i].begin(), searchWords[i].end(), searchWords[i].begin(), ::tolower);
          currentQ->addorArgs(searchWords[i]);
        }
        break;
      }
    case 2:
      {
        for(int i = 0; i < searchWords.size(); i++)
        {
          transform(searchWords[i].begin(), searchWords[i].end(), searchWords[i].begin(), ::tolower);
          currentQ->addnormArgs(searchWords[i]);
        }
        break;
      }
    }
}

void QueryProcessor::print()
{
  currentQ->printQuery();
}


vector<Page*> QueryProcessor::searchIndex(string search_string, IndexHandler*& ih)
{
  cout << search_string << endl;
  parseQuery(search_string);
  //check for AND args

  if (currentQ->getandArgs().size() > 0)
  {
    vector<Page*> andResultSet;
    set<Page*>a = ih->searchIndex(currentQ->getandArgs()[0]);
    set<Page*>b = ih->searchIndex(currentQ->getandArgs()[1]);

    /*for (auto e: a)
      cout << e->getTitle() << endl;

    for (auto e: b)
      cout << e->getTitle() << endl;*/


    set_intersection(a.begin(), a.end(), b.begin(), b.end(), andResultSet.begin());
    cout << "something" << endl;
    cout << andResultSet[0]->getTitle() << endl;
    return andResultSet;

    /*set<Page*> andResultSet = ih->searchIndex(currentQ->getandArgs()[0]);
    if (currentQ->getandArgs().size() > 1)
      for (auto e: currentQ->getandArgs())
        set_intersection(andResultSet.begin(), andResultSet.end(), ih->searchIndex(e).begin(), ih->searchIndex(e).end(), inserter(andResultSet,andResultSet.begin()));*/
  }
  else if (currentQ->getnormArgs().size() > 0)
  {
    set<Page*> a = ih->searchIndex(currentQ->getnormArgs()[0]);
    vector<Page*> results(a.begin(), a.end());
    return results;
  }
}
