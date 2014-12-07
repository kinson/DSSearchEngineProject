#include "QueryProcessor.h"
#include "stemHelper.h"


QueryProcessor::QueryProcessor()
{
  currentQ = new Query();
}

QueryProcessor::~QueryProcessor()
{}

void QueryProcessor::parseQuery(std::string search)
{
  searchQuery = search;
	istringstream inString(searchQuery);
  searchWords.clear();

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


vector<Result*> QueryProcessor::searchIndex(string search_string, IndexHandler*& ih)
{
  parseQuery(search_string);
  //check different types of arguments
  vector<Page*>results;
  if (currentQ->getandArgs().size() > 0)
  {
    for (auto e: currentQ->getandArgs())
    {
      if (results.size() > 0)
      {
        set<Page*>test(results.begin(), results.end());
        results.clear();
        set<Page*> andargs = ih->searchIndex(e);
        set_intersection(test.begin(), test.end(), andargs.begin(), andargs.end(), back_inserter(results));
      }
      else
      {
        set<Page*> andargs = ih->searchIndex(e);
        copy(andargs.begin(), andargs.end(), back_inserter(results));
      }
    }
  }
  else if (currentQ->getorArgs().size() > 0)
  {
    set<Page*>orResultSet;
    for (auto e: currentQ->getorArgs())
    {
      set<Page*> a = ih->searchIndex(e);
      orResultSet.insert(a.begin(), a.end());
    }
    copy(orResultSet.begin(), orResultSet.end(), back_inserter(results));
  }
  else if (currentQ->getnormArgs().size() > 0)
  {
    set<Page*> a = ih->searchIndex(currentQ->getnormArgs()[0]);
    copy(a.begin(), a.end(), back_inserter(results));
  }
  if (currentQ->getnotArgs().size() > 0)
  {
    for (auto e: currentQ->getnotArgs())
    {
      set<Page*>test(results.begin(), results.end());
      results.clear();
      set<Page*> notargs = ih->searchIndex(e);
      set_difference(test.begin(), test.end(), notargs.begin(), notargs.end(), back_inserter(results));
    }
  }
  vector<Result*> resultsvector = sortResults(results);
  return resultsvector;
}


vector<Result*> QueryProcessor::sortResults(vector<Page*>& unsortedResults)
{
  vector<double>resultsinversefreq;
  //if there are AND arguments
  if (currentQ->getandArgs().size() > 0)
  {
    //for each Page* object in the unsorted results vector
    for (auto e:unsortedResults)
    {
      //cout << "processing " << e->getTitle() << endl;
      double freq = 0;
      double sumwords = 0;
      //for each keyword string in the page object
      for (int i = 0; i < e->getKeywords().size(); i++)
      {
        //for each of the and arguments
        for (auto arg: currentQ->getandArgs())
          if (arg == e->getKeywordAtIndex(i))
          {
            //cout << "\tcounting " << e->getKeywordAtIndex(i) << " " << e->getFrequency(i) << endl;
            freq += e->getFrequency(i); //argument found in page
            break;
          }
        sumwords+=1; //incremenet number of words
      }

      //do the math
      resultsinversefreq.push_back(freq/sumwords);
    }
  }
  else if(currentQ->getorArgs().size() > 0)
  {
    for (auto e: unsortedResults)
    {
      double freq = 0;
      double sumwords = 0;
      //for each keyword string in the page object
      for (int i = 0; i < e->getKeywords().size(); i++)
      {
        //for each of the or arguments
        for (auto arg: currentQ->getorArgs())
          if (arg == e->getKeywordAtIndex(i))
          {
            freq += e->getFrequency(i); //argument found in page
            break;
          }
        sumwords+=1; //incremenet number of words
      }

      //do the math
      resultsinversefreq.push_back(freq/sumwords);
    }
  }
  else //if there is only one search term
  {
    //for each Page* object in the unsorted results vector
    for (auto e:unsortedResults)
    {
      double freq = 0;
      double sumwords = 0;
      //for each keyword string in the page object
      for (int i = 0; i < e->getKeywords().size(); i++)
      {
        if (currentQ->getnormArgs()[0] == e->getKeywordAtIndex(i))
          freq += e->getFrequency(i); //argument found in page
        sumwords+=1; //incremenet number of words
        break;
      }
      //do the math
      resultsinversefreq.push_back(freq/sumwords);
    }
  }

  vector<Result*>results;
  //now sort
  for (int i = 0; i < unsortedResults.size(); i++)
  {
    Result* rs = new Result(unsortedResults[i], resultsinversefreq[i]);
    results.push_back(rs);
  }


  //sort the results
  results = merge_sort(results);

  if (results.size() > 15)
    results.erase(results.begin()+15, results.end());

  return results;
}


vector<Result*> QueryProcessor::merge_sort(vector<Result*>& vec)
{
  // Termination condition: List is completely sorted if it
  // only contains a single element.
  if(vec.size() == 1)
  {
    return vec;
  }

  // Determine the location of the middle element in the vector
  vector<Result*>::iterator middle = vec.begin() + (vec.size() / 2);

  vector<Result*> left(vec.begin(), middle);
  vector<Result*> right(middle, vec.end());

  // Perform a merge sort on the two smaller vectors
  left = merge_sort(left);
  right = merge_sort(right);

  return merge(vec,left, right);
}

vector<Result*> QueryProcessor::merge(vector<Result*> &vec,const vector<Result*>& left, const vector<Result*>& right)
{
  // Fill the resultant vector with sorted results from both vectors
  vector<Result*> result;
  unsigned left_it = 0, right_it = 0;

  while(left_it < left.size() && right_it < right.size())
  {
    // If the left value is smaller than the right it goes next
    // into the resultant vector
    if(left[left_it]->getInverseFrequency() > right[right_it]->getInverseFrequency())
    {
      result.push_back(left[left_it]);
      left_it++;
    }
    else
    {
      result.push_back(right[right_it]);
      right_it++;
    }
  }

  // Push the remaining data from both vectors onto the resultant
  while(left_it < left.size())
  {
    result.push_back(left[left_it]);
    left_it++;
  }

  while(right_it < right.size())
  {
    result.push_back(right[right_it]);
    right_it++;
  }
  //take a source vector and parse the result to it. then return it.
  vec = result;
  return vec;
}
