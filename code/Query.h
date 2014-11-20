#ifndef QUERY_H
#define QUERY_H

#include <vector>


class Query
{
public:
	Query();
	Query(std::vector<std::string>,std::vector<std::string>,std::vector<std::string>);
	std::vector<std::string> getandArgs();
	std::vector<std::string> getorArgs();
	std::vector<std::string> getnotArgs();
	~Query();

private:
	std::vector<std::string> andArgs;
	std::vector<std::string> orArgs;
	std::vector<std::string> notArgs;
};

#endif 