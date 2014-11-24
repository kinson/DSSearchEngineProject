#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
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

	private:
};

#endif 