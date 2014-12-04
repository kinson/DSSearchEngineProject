#include "DocumentParser.h"
#include "stemHelper.h"


/***********************************************************************************************
                                          GOT STEMMER HERE
                    https://bitbucket.org/smassung/porter2_stemmer/wiki/Home
************************************************************************************************/

DocumentParser::DocumentParser()
{
  //load stop words
  ifstream stopWordsIn;
  stopWordsIn.open("stopwords.txt");
  string word;
  while(!stopWordsIn.eof())
  {
    stopWordsIn >> word;
    stopwords[word] = true;
  }
  stopWordsIn.close();

  //load bad phrase file
  ifstream badPhrasesIn;
  badPhrasesIn.open("badphrase.txt");
  while(!badPhrasesIn.eof())
  {
    badPhrasesIn >> word;
    throwout.push_back(word);
  }
  badPhrasesIn.close();
  sort(throwout.begin(), throwout.end());

}

void DocumentParser::parseDrive(string xmlInFile, IndexHandler*& indexhandler)
{
  //create ifstream object to read in xmlfile
  ifstream inFile(xmlInFile.c_str());
  stringstream inXMLstream;
  //read it all in
  inXMLstream << inFile.rdbuf();
  inFile.close();
  int counter = 0;
  int looper = 0; //used to only get a certain amount of xml file
  string inString;
  cout << "<";

  while(!inXMLstream.eof() && looper < 20000)
  {
    //read in next word
    inXMLstream >> inString;

    //found new page object, now parse it
    if (inString.compare(0, 5, "<page") == 0)
    {
        //create page object to save data in
        Page* page = new Page();

        /***********************************************************************************************
                                                    FIND TITLE
        ************************************************************************************************/
        string title = "";

        while(inString.compare(0, 7, "<title>") != 0)
          inXMLstream >> inString;

        //handle if there isn't a space between tag and title i.e. <title>Main
        if (inString.length() > 7)
          inString = inString.substr(7, inString.length());
        else
          inXMLstream >> inString;


        while(inString.compare(0, 7, "</title>") != 0)
        {
          //check to see if last part of title is tacked on to element and break if so
          if (inString.length() > 7)
            if (inString.compare(inString.length() - 8, inString.length(), "</title>") == 0)
              break;

          title += inString + " ";
          inXMLstream >> inString;
        }

        //check to see if last part of title is tacked on to element i.e. text</title>
        if (inString.length() > 7 && inString.compare(inString.length() - 8, inString.length(), "</title>") == 0)
        {
          title += inString.substr(0, inString.length()-8);
        }
        page->setTitle(title);

        /***********************************************************************************************
                                                    FIND ID
        ************************************************************************************************/
        string id = "";

        while(inString.compare(0, 4, "<id>") != 0)
          inXMLstream >> inString;

        //handle space between tag and id number
        if (inString.length() > 4)
          id = inString.substr(4, inString.length());
        else
          inXMLstream >> id;

        if (id.length() > 4 && inString.compare(inString.length() - 5, inString.length(), "</id>") == 0)
        {
          id = id.substr(0, id.length()-5);
        }

        page->setId(atoi(id.c_str()));

        /***********************************************************************************************
                                                FIND USERNAME
        ************************************************************************************************/

        string username = "";
        bool noUser = false;

        while(inString.compare(0, 13, "<contributor>") != 0)
          inXMLstream >> inString;

        //see if there isn't a username give for contributor
        while(inString.compare(0, 10, "<username>") != 0)
        {
          if (inString.length() > 13 && inString.compare(inString.length() -14, inString.length(), "</contributor>"))
          {
            noUser = true;
            break;
          }
          inXMLstream >> inString;
        }

        //only search for the username if we know it's there
        if(noUser == false)
        {
          if (inString.length() > 10)
            inString = inString.substr(10, inString.length());
          else
            inXMLstream >> inString;


          while(inString.compare(0, 10, "</username>") != 0)
          {
            //check to see if last part of username is tacked on to element and break if so
            if (inString.length() > 10)
              if (inString.compare(inString.length() - 11, inString.length(), "</username>") == 0)
                break;

            username += inString + " ";
            inXMLstream >> inString;
          }

          //check to see if last part of username is tacked on to element
          if (inString.length() > 7 && inString.compare(inString.length() - 11, inString.length(), "</username>") == 0)
          {
            username += inString.substr(0, inString.length()-11);
          }
        }
        else
          username = "none";

        page->setContributingUser(username);

        cout << looper++ << "\t" << title << " by " << username << " has id " << id << endl;


        /***********************************************************************************************
                                            FIND KEYWORDS
        ************************************************************************************************/
        while(inString.compare(0, 5, "<text") != 0)
          inXMLstream >> inString;
        bool isStop;
        while(inString.compare("</text") != 0)
        {
          isStop = false;
          if(inString.length() > 6 && inString.compare(inString.length()-7, inString.length(), "</text>") == 0)
            break;

          //make the string lower case
          transform(inString.begin(), inString.end(), inString.begin(), ::tolower);

          //search for keyword in stop word list, n times complexity, could be binary search
          if (stopwords.count(inString))
              isStop = true;

          //if it's not being thrown out
          if(!isStop && inString.length() > 2)
          {
               inString.erase(std::remove_if(inString.begin(), inString.end(), [](char thing){
                  if((int) thing >= 122 || (int) thing <= 97) return true;
                  else return false;
               }), inString.end());
            char* buffer = (char*) inString.c_str();
           string newString = StemHelper::stemword(buffer);
           page->addKeyword(inString);
          }

          //read in next word
          inXMLstream >> inString;

        }
      collection.push_back(page);
    }

  }
  cout << ">" << endl;

}


void DocumentParser::writeToStructure(IndexHandler*& ih, int startIndex)
{
  for(int i = startIndex; i < collection.size(); i++)
    ih->addPage(collection[i]);
}

void DocumentParser::saveIndex()
{
  ofstream indexSave("index.txt");
  for (int i = 0; i < collection.size(); i++)
  {
    Page* t = collection[i];
    indexSave << t->getTitle() << endl;
    indexSave << t->getId() << endl;
    //indexSave << t->getDate() << endl;
    indexSave << t->getContributingUser() << endl;
    indexSave << t->getKeywords().size() << endl;
    int largeindex = t->getKeywords().size();
    for (auto e: t->getKeywords())
      indexSave << e << endl;
  }
  indexSave.close();

}

void DocumentParser::readInParsedFile(IndexHandler*& indexhandler)
{
  ifstream indexRead("index.txt");
  string inString;
  int looper = 0;
  while (!indexRead.eof() /*&& looper++ < 5*/)
  {
    Page* p = new Page();
    getline(indexRead, inString);
    p->setTitle(inString);
    //cout << ++looper <<  " title: " << inString;
    getline(indexRead, inString);
    p->setId(atoi(inString.c_str()));
    //cout << " id: " << inString;
    getline(indexRead, inString);
    p->setContributingUser(inString);
    //cout << " user: " << inString << endl;
    getline(indexRead, inString);
    int test = 0;
    int number_of_pages = atoi(inString.c_str());
    for (int i = 0; i < number_of_pages; i++)
    {
      getline(indexRead, inString);
      p->addKeyword(inString);
      //cout <<++test << " " << inString << endl;
    }

    collection.push_back(p);
    //cout << p->getTitle() << " " << p->getId() << " " << "number of pages " << number_of_pages << p->getContributingUser() << endl;
  }
}

int DocumentParser::getCollectionSize()
{
  return collection.size() - 1;
}
