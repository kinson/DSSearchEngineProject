#include "DocumentParser.h"

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
    stopwords.push_back(word);
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

}

void DocumentParser::parseDrive(string xmlInFile)
{
  //create ifstream object to read in xmlfile
  ifstream inXMLstream;
  inXMLstream.open(xmlInFile.c_str());
  int counter = 0;
  int looper = 0; //used to only get a certain amount of xml file
  while(!inXMLstream.eof() /*&& looper++ < 130*/)
  {
    //read in next word
    string inString;
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


        while(inString.compare(0, 7, "</title>") !=0)
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

        cout << title << " by " << username << " has id " << id << endl;


        /***********************************************************************************************
                                  FIND KEYWORDS //still need to parse out formatting shit
        ************************************************************************************************/
        while(inString.compare(0, 5, "<text") != 0)
          inXMLstream >> inString;
        bool isStop;
        while(inString.compare("</text") != 0)
        {
          isStop = false;
          if(inString.length() > 6 && inString.compare(inString.length()-7, inString.length(), "</text>") == 0)
            break;
          //read in next word
          inXMLstream >> inString;

          for (int i = 0; i < inString.length(); i++)
          {
            if(inString.substr(i) == "&" || inString.substr(i) == "," || inString.substr(i) == ";" || inString.substr(i) == "." || inString.substr(i) == "]" || inString.substr(i) == "|")
            {
              inString = inString.substr(0, i);
            }
          }
          //make the string lower case
          transform(inString.begin(), inString.end(), inString.begin(), ::tolower);
          //search for keyword in stop word list, n times complexity, could be binary search
          for(size_t i = 0; i < stopwords.size(); i++)
          {
            if(inString.compare(stopwords[i]) == 0) //this fucking == cost me 30 minutes alone
            {
              isStop = true;
              break;
            }
          }
          for (size_t i = 0; i < throwout.size(); i++)
          {
            if (inString.find(throwout[i])!= string::npos)
            {
              //cout << inString << endl;
              isStop = true;
              break;
            }
          }

          if(!isStop)
          {
            Porter2Stemmer::stem(inString);
            page->addKeyword(inString);
          }

        }
        /*for(auto e: page->getKeywords())
          cout << e << endl;*/

        collection.push_back(page);
        cout << counter++ << endl;
    }

  }
  inXMLstream.close();


}
