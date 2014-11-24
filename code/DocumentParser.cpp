#include "DocumentParser.h"
#include "PorterStemmer.h"
//int stem(char * p, int i, int j);

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

void DocumentParser::parseDrive(string xmlInFile)
{
  struct stemmer * z = create_stemmer();
  //create ifstream object to read in xmlfile
  ifstream inFile(xmlInFile.c_str());
  stringstream inXMLstream;
  //inFile.seekg(0, ios::end);
  //unsigned long fileSize = inFile.tellg();
  //cout << "file size is " << fileSize << endl;
  //read it all in
  inXMLstream << inFile.rdbuf();
  inFile.close();
  /*char* chararray = new char[fileSize+1];
  inFile.open(xmlInFile.c_str());
  inFile.read(chararray, fileSize);
  inFile.close();
  cout << chararray << endl;*/
  int counter = 0;
  int looper = 0; //used to only get a certain amount of xml file
  string inString;

  while(!inXMLstream.eof() && looper < 4)
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

        cout << looper++ << "\t" << title << " by " << username << " has id " << id << endl;


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

          /*for (int i = 0; i < inString.length(); i++) //3:14 with just this
          {
            if(inString.substr(i) == "&" || inString.substr(i) == "," || inString.substr(i) == ";" || inString.substr(i) == "." || inString.substr(i) == "]" || inString.substr(i) == "|")
            {
              inString = inString.substr(0, i);
            }
          }*/
          //make the string lower case
          transform(inString.begin(), inString.end(), inString.begin(), ::tolower);
          //search for keyword in stop word list, n times complexity, could be binary search
          if (stopwords.count(inString)) //15% in 5 min
            isStop = true;
          /*for (size_t i = 0; i < throwout.size(); i++)
          {
            if (inString.find(throwout[i])!= string::npos)
            {
              isStop = true;
              break;
            }
          }*/
          //if it's not being thrown out
          if(!isStop)
          {
            char* buffer = new char[80];
            for(int i = 0; i< inString.size(); i++)
            {
              buffer[i] = inString.at(i);
            }  

            int whoknowswhatthisis = stem(z, buffer, inString.length());
            //Porter2Stemmer::stem(inString);
            //page->addKeyword(inString);
          }

        }

        collection.push_back(page);
    }

  }

}


void DocumentParser::writeToStructure(IndexHandler*& indexhandler)
{

  for (auto e: collection)
    indexhandler->addPage(e);
}
