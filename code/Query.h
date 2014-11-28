#ifndef QUERY_H
#define QUERY_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Query
{
public:
	Query();
	Query(std::vector<std::string>,std::vector<std::string>,std::vector<std::string>);
	std::vector<std::string> getandArgs();
	std::vector<std::string> getorArgs();
	std::vector<std::string> getnotArgs();
	void addandArgs(std::string);
	void addorArgs(std::string);
	void addnotArgs(std::string);
	void addnormArgs(std::string);
	void printQuery();
	~Query();

private:
	std::vector<std::string> andArgs;
	std::vector<std::string> orArgs;
	std::vector<std::string> notArgs;
	std::vector<std::string> normArgs;
};

#endif 