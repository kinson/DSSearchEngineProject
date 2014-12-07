#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include "IndexHandler.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "QueryProcessor.h"
#include "DocumentParser.h"
#include "Result.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

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


		bool fexists(const std::string&); //return true if file exists
		void clearIndex(); //destruct index if it exists
		void addFilesToIndex(); //add file to paths vector if it exists
		void addFilesToIndex(std::string); //add file to paths vector if it exists give path
		void createStructure(std::string); //create indexhandler structure based on arg
		void addToExistingIndex(); //add more files!
		void searchIndex(); //search the indexhandler and display results
		void loadExistingIndex(); //load indexed file into memory
		void saveIndexToDisk();


	private:
		IndexHandler* indexhandler;
		DocumentParser* docparser;
		QueryProcessor* qprocessor;
		vector<std::string>paths;
};

#endif
