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
	while(userChoice!=0)
	{
		cout << "Welcome!" << endl << "Enter the number of the mode you wish to use." << endl;
		cout << "1: Maintenence Mode" << endl;
		cout << "2: Interactive Mode" << endl;
		cout << "3: Stress Test Mode" << endl;
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
	cout << "Enter the number of what you want YO!" << endl;
	cout << "1: Add files to the index " << endl;
	cout << "2: Clear Index " << endl;
	cout << "0: Exit Maintence mode" << endl;
	cin >> maintenence;

	switch(atoi(maintenence.c_str()))
	{
		case (1):
			addFilesToIndex(); //add files to index
			addToExistingIndex();
			break;
		case(2):
			clearIndex();
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
	cout << "Enter the number of what you want YO!" << endl;
	if (indexhandler == nullptr)
	{
		cout << "Index Status: No index created" << endl;
		cout << "1: Create Hash Table" << endl;
		cout << "2: Create AVL Tree" << endl;
		cout << "0: Exit Maintence mode" << endl;
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
		cout << "Index Status: " << (indexhandler->getClassType() == "HashTable" ? "Hash Table" : "AVL Tree")  << "filled with " << docparser->getCollectionSize() << " pages" << endl;
		cout << "1: Search Index" << endl;
		cout << "2: Clear Index" << endl;
		cout << "3: Switch to " << (indexhandler->getClassType() == "HashTable" ? "AVL Tree" : "Hash Table") << endl;
		cout << "0: Exit" << endl;
	}

}

void UserInterface::stressTest()
{
	string stressFile;
	cout << endl << endl << "Welcome to the Stress Test" << endl;
	cout << "Enter the name of the file you wish to upload" << endl;
	cin >> stressFile;
}


void UserInterface::createStructure(string structtype)
{
	//check to see if indexhandler is already a structure
	if (indexhandler != nullptr)
	{
		clearIndex();
	}

	if (structtype == "HashTable")
		indexhandler = new HashTable();
	else
		indexhandler = new AVLTree();

	//check for exmpty list
	if (paths.size() > 0)
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
		indexhandler->destroyStructure();
		delete indexhandler;
	}
}


void UserInterface::addToExistingIndex()
{
	int lastCollectionIndex = docparser->getCollectionSize();
	docparser->parseDrive(paths[paths.size()-1], indexhandler);
	docparser->writeToStructure(indexhandler, lastCollectionIndex + 1);
}
