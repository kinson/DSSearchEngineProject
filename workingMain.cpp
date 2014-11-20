#include <iostream> 
#include <string>
#include <vector>
#include "QueryProcessor.h"

using namespace std;

int main()
{
	cout << "I'm creating a query processor" << endl;
	QueryProcessor* QP = new QueryProcessor();
	QP->parseQuery("I am morgan Monzingo yo");
	return 0;
}