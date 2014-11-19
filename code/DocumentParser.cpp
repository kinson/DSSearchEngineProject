#include "DocumentParser.h"



DocumentParser::DocumentParser()
{

}

void DocumentParser::parseDrive(string xmlInFile)
{
  //create ifstream object to read in xmlfile
  ifstream inXMLstream;
  inXMLstream.open(xmlInFile.c_str());
  int counter = 0;
  int looper = 0; //used to only get a certain amount of xml file
  while(!inXMLstream.eof() && looper++ < 5000)
  {
    //read in next word
    string inString;
    inXMLstream >> inString;
    //found new page object, now parse it
    if (inString.compare(0, 5, "<page") == 0)
    {
        string title = "";

        /***********************************************************************************************
                                                    FIND TITLE
        ************************************************************************************************/

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

    }
  }

}
