/** Query header file
*holds each keyword needing to be searched in query
*Sam Hunter and Morgan Monzingo
*/

#ifndef QUERY_H
#define QUERY_H

#include <vector>
#include <string>
#include <iostream>

//using namespace std;


class Query
{
public:
	Query();
	//returns vectors 
	std::vector<std::string> getandArgs();
	std::vector<std::string> getorArgs();
	std::vector<std::string> getnotArgs();
	std::vector<std::string> getnormArgs();
	//returns at specified index of query
	std::string getandArgs(int);
	std::string getorArgs(int);
	std::string getnotArgs(int);
	std::string getnormArgs(int);
	//sets query
	void setandArgs(int, std::string);
	void setorArgs(int,std::string);
	void setnotArgs(int,std::string);
	void setnormArgs(int,std::string);
	//adds each word into query
	void addandArgs(std::string);
	void addorArgs(std::string);
	void addnotArgs(std::string);
	void addnormArgs(std::string);
	void clearQuery();
	~Query();

private:
	std::vector<std::string> andArgs;
	std::vector<std::string> orArgs;
	std::vector<std::string> notArgs;
	std::vector<std::string> normArgs;
};

#endif
