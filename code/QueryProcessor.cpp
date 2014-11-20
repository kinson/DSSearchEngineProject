#include "QueryProcessor.h"

QueryProcessor::QueryProcessor()
{

}

QueryProcessor::~QueryProcessor()
{

}
void QueryProcessor::parseQuery(std::string search)
{
	searchQuery = search;
	istringstream inString(searchQuery);
	cout << searchQuery << endl;
    while (inString)
    {
      string temp;
      if (!getline( inString, temp, ' ' )) 
      	break;
      searchWords.push_back( temp );
    }

    for(int i = 0; i < searchWords.size(); i++)
    	cout << searchWords[i] << endl << endl;
	
}