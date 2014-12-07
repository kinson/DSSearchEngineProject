#include "UserInterface.h"


UserInterface::UserInterface()
{
	docparser = new DocumentParser();
	qprocessor = new QueryProcessor();
	indexhandler = nullptr;
}

UserInterface::~UserInterface()
{

}

void UserInterface::driver()
{
	int userChoice = 1;
	while(userChoice != 0)
	{
		cout << "Welcome!" << endl << "Enter the number of the mode you wish to use." << endl;
		cout << "1: Maintenence Mode" << endl;
		cout << "2: Interactive Mode" << endl;
		cout << "3: Stress Test Mode" << endl;
		cout << "0: Exit Program" << endl;
		cin >> userChoice;

		switch(userChoice)
		{
			case 0:
			{
				cout << "Have a wonderful day!";
				break;
			}
			case 1:
			{
				maintenenceMode();
				break;
			}
			case 2:
			{
				interactiveMode();
				break;
			}
			case 3:
			{
				stressTest();
				break;
			}
			default:
			{
				cout << "You have entered an invalid number" << endl;
				break;
			}
		}

	}
}

void UserInterface::maintenenceMode()
{
	string maintenence;
	cout << endl << endl << "Welcome to Maintenence Mode" << endl;
	cout << "1: Add files to the index " << endl;
	cout << "2: Clear index " << endl;
	if (indexhandler != nullptr)
		cout << "3: Save index to disk" << endl;
	if (fexists("index.txt") && indexhandler == nullptr)
		cout << "4: Load existing index" << endl;
	cout << "0: Exit maintence mode" << endl;
	cin >> maintenence;

	switch(atoi(maintenence.c_str()))
	{
		case (1):
			addFilesToIndex(); //add files to index
			docparser->parseDrive(paths[paths.size()-1], indexhandler);
			addToExistingIndex();
			break;
		case(2):
			clearIndex();
			break;
		case(3):
			saveIndexToDisk();
			break;
		case(4):
			loadExistingIndex();
			break;
		case(0):
			return;
		default:
			cout << "Please choose an option or exit back to main screen" << endl;
	}
	maintenenceMode();
}

void UserInterface::interactiveMode()
{
	string interaction;
	cout << endl << endl << "Welcome to Interactive Mode" << endl;
	if (indexhandler == nullptr)
	{
		cout << "Index Status: No index created" << endl;
		cout << "1: Create Hash Table" << endl;
		cout << "2: Create AVL Tree" << endl;
		cout << "0: Exit interactive mode" << endl;
		cin >> interaction;
		switch(atoi(interaction.c_str()))
		{
			case(1):
				createStructure("HashTable");
				break;
			case(2):
				createStructure("AVLTree");
				break;
			case(0):
				return;
			default:
				cout << "Please choose an option or exit back to main screen" << endl;
		}
		interactiveMode();
	}
	else
	{
		cout << "Index Status: " << (indexhandler->getClassType() == "HashTable" ? "Hash Table" : "AVL Tree")  << " filled with " << docparser->getCollectionSize() << " pages" << endl;
		cout << "1: Search Index" << endl;
		cout << "2: Clear Index" << endl;
		cout << "3: Switch to " << (indexhandler->getClassType() == "HashTable" ? "AVL Tree" : "Hash Table") << endl;
		cout << "0: Exit interactive mode" << endl;
		cin >>interaction;
		switch(atoi(interaction.c_str()))
		{
			case(1):
				searchIndex();
				break;
			case(2):
				clearIndex();
				break;
			case(3):
				createStructure(indexhandler->getClassType() == "HashTable" ? "AVLTree" : "HashTable");
				break;
			case(0):
				return;
			default:
				cout << "Please choose an option or exit back to main screen" << endl;
		}
		interactiveMode();
	}

}

void UserInterface::stressTest()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	ifstream stress;

	string stressFile;
	string doFunc;
	string path;
	string searchQ;
	string indexType;
	string holder;
	cout << endl << endl << "Welcome to the Stress Test" << endl;
	cout << "Enter the name of the file you wish to upload" << endl;
	cin >> stressFile;
	stress.open(stressFile);

	while(stress.good()) //use the better one
	{	
		start = std::chrono::system_clock::now();
		stress >> doFunc;
		if(doFunc.compare("AF")==0)
		{
			cout << "Adding files..." << endl;
			stress >> path;
			addFilesToIndex(path);
		}

		if(doFunc.compare("PD")==0)
		{
			stress >> path;
			cout << "parsing..." << endl;
			docparser->parseDrive(path, indexhandler);
		}

		if(doFunc.compare("SQ")==0)
		{
			cout << "searching..." << endl;
			stress >> searchQ;
			stress >> holder;
			while(holder.size()>2)
			{
				searchQ = " "  + holder;
				stress >> holder;
			}
			cout << searchQ << endl;

			vector<Result*> results = qprocessor->searchIndex(searchQ, indexhandler);
			if (results.size() > 0)
				for (auto e: results)
					cout << e->getTitle() << endl;
			else
				cout << "no results found in data set" << endl;
		}

		if(doFunc.compare("CS")==0)
		{
			cout << "creating structure..." << endl;
			stress >> indexType;
			if(indexType.compare("HashTable")==0)
			{
				indexhandler = new HashTable();
			}

			else
				indexhandler = new AVLTree();


			docparser->readInParsedFile(indexhandler);
			docparser->writeToStructure(indexhandler);
		}

		if(doFunc.compare("SI")==0)
		{
			cout << "saving to index.." << endl;
			saveIndexToDisk();
		}

		if(doFunc.compare("CI")==0)
		{
			cout << "clear index..." << endl;
			clearIndex();
		}

		end = std::chrono::system_clock::now();
		unsigned int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
		std::cout << " Time: " << milliseconds << " seconds" << std::endl;
	}
}

void UserInterface::createStructure(string structtype)
{
	//check to see if indexhandler is already a structure
	/*if (indexhandler != nullptr)
	{
		clearIndex();
	}*/

	if (structtype == "HashTable")
		{cout<< "this creates a hashtable";
		indexhandler = new HashTable();}
	else
		indexhandler = new AVLTree();

	//check for exmpty list
	if (docparser->getCollectionSize() > 0)
	{
		addToExistingIndex();
	}
	else if (paths.size() > 0)
	{
		for (auto e: paths)
			docparser->parseDrive(e, indexhandler);
	}
	else
	{
		cout << "no xml files present, please add at least one valid path" << endl;
		addFilesToIndex();
		addToExistingIndex();
	}

}

void UserInterface::addFilesToIndex()
{
	string xmlPath;
	cout << "Enter relative path to xml document" << endl;
	cin >> xmlPath;
	//check to see if the file actually exists
	if (xmlPath == "0")
		return;
	if (!fexists(xmlPath))
	{
		cout << "Please enter a valid path" << endl;
		addFilesToIndex();
	}
	//check to see if path already exists in the vector
	bool inVector = false;
	for (auto e: paths)
		if (e == xmlPath)
		{
			cout << "Path already exists" << endl;
			inVector = true;
		}
	if (!inVector)
		paths.push_back(xmlPath);

}

void UserInterface::addFilesToIndex(string xmlPath)
{
		paths.push_back(xmlPath);
}

bool UserInterface::fexists(const string& filename)
{
	ifstream ifile(filename.c_str());
	if (!ifile)
		return false;
	return true;
}

void UserInterface::clearIndex()
{

	if (indexhandler != nullptr)
	{
		docparser->clearCollection();
		paths.clear();
		//indexhandler->destroyStructure();
		//delete indexhandler;
	}
}


void UserInterface::addToExistingIndex()
{
	int lastCollectionIndex = docparser->getCollectionSize();
	//docparser->parseDrive(paths[paths.size()-1], indexhandler);
	if (indexhandler == nullptr)
	{
		cout << "Select a data structure to write to\n1: Hash Table\n2: AVL Tree" << endl;
		string input;
		cin >> input;
		if (input == "1")
			indexhandler = new HashTable();
		else if (input == "2")
			indexhandler = new AVLTree();
		else
		{
			cout << "invalid choice" << endl;
			return;
		}
	}
	docparser->writeToStructure(indexhandler);
}

void UserInterface::searchIndex()
{
	cin.ignore();
	cout << "Enter search query" << endl;
	string query;
	getline(cin, query);
	vector<Result*> results = qprocessor->searchIndex(query, indexhandler);

	int resultnum = 0;
	int resultchoice = -1;
	if (results.size() > 0)
	{
		for (auto e: results)
		{
			cout << endl << "RESULT\t" << resultnum++ << "------------------------------" << endl;
			cout << e->getTitle() << endl;
			cout << "id: " << e->getId() << endl << "user: " << e->getPage()->getContributingUser() << endl << "date: " << e->getDate() << endl << "TD/IDF: " << e->getInverseFrequency() << endl;
		}
		cout << "Enter a result number to see full text or type -1 to return to menu: ";
		cin >> resultchoice;
		if (resultchoice != -1)
			cout << results[resultchoice]->getTitle() << endl << results[resultchoice]->getFullText() << endl;

	}
	else
		cout << "no results found in data set" << endl;

}

void UserInterface::loadExistingIndex()
{
	if (indexhandler == nullptr)
	{
		cout << "Select a data structure to write to\n1: Hash Table\n2: AVL Tree" << endl;
		string input;
		cin >> input;
		if (input == "1")
			indexhandler = new HashTable();
		else if (input == "2")
			indexhandler = new AVLTree();
		else
		{
			cout << "invalid choice" << endl;
			return;
		}
	}

	docparser->readInParsedFile(indexhandler);
	docparser->writeToStructure(indexhandler);

}

void UserInterface::saveIndexToDisk()
{
	docparser->saveIndex();
}
