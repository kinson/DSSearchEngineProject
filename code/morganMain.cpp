#include "QueryProcessor.h"
#include <iostream>

using namespace std;

int main()
{

	QueryProcessor* fake = new QueryProcessor();
	fake->parseQuery("and I am including all of these words but not any of the words over here because they stink");

	return 0;
}