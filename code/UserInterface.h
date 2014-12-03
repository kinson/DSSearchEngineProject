#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "IndexHandler.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "QueryProcessor.h"
#include "DocumentParser.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class UserInterface
{
	public:
		UserInterface();
		~UserInterface();
		void driver();
		void maintenenceMode();
		void interactiveMode();
		void stressTest();


		bool fexists(const string&); //return true if file exists
		void clearIndex(); //destruct index if it exists
		void addFilesToIndex(); //add file to paths vector if it exists
		void createStructure(string); //create indexhandler structure based on arg
		void addToExistingIndex(); //add more files!
		void searchIndex(); //search the indexhandler and display results
		void loadExistingIndex(); //load indexed file into memory


	private:
		IndexHandler* indexhandler;
		DocumentParser* docparser;
		QueryProcessor* qprocessor;
		vector<string>paths;
};

#endif
