#ifndef QUERY_H
#define QUERY_H

#include <vector>


class Query
{
public:
	Query();
	~Query();
private:
	std::vector<std::string> andArgs;
	std::vector<std::string> orArgs;
	std::vector<std::string> notArgs;
};

#endif 