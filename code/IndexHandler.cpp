#include "IndexHandler.h"

IndexHandler::IndexHandler()
{}

void IndexHandler::addPage(Page* nextPage)
{

	//read in the keywords of the specific page
	vector<string> temp = nextPage.getKeywords();
	int size = temp.size();

	//add pages with each keyword
	for(int i = 0; i < size; i++)
	{
		addToIndex(nextPage, temp(i));
	}
	
}

void addToIndex(Page* page, string keyword)
{
	
}