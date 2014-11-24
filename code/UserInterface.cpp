#include "UserInterface.h"

UserInterface::UserInterface()
{
	
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
	int maintence = 0;
	cout << endl << endl << "Welcome to Maintenence Mode" << endl;
	cout << "Enter the number of what you want YO!" << endl;
	cout << "1: Add files to the index " << endl;
	cout << "2: Clear Index " << endl;
	cout << "0: Exit Maintence mode" << endl;
	cin >> maintence;
}

void UserInterface::interactiveMode()
{
	int interaction;
	cout << endl << endl << "Welcome to Interactive Mode" << endl;
	cout << "Enter the number of what you want YO!" << endl;
	cout << "1: Choose Index str" << endl;
	cout << "2: Clear Index " << endl;
	cout << "0: Exit Maintence mode" << endl;
	cin >> interaction;
}

void UserInterface::stressTest()
{
	string stressFile;
	cout << endl << endl << "Welcome to the Stress Test" << endl;
	cout << "Enter the name of the file you wish to upload" << endl;
	cin >> stressFile;
}


































