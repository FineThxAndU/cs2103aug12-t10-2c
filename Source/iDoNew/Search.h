#ifndef SEARCH_H
#define SEARCH_H
#include "Task.h"
#include <string>
#include <vector>
#include <time.h>

class Search
{
	vector<Task*> inputList, searchResults;
	vector<int> resultIndices;
	

	public:
		void setInputList(vector<Task*> list);
		
		bool executeSearch(string criteria);
		bool executeSearch(Task* query);
		vector<int> getIndices ();
		vector<Task*> getResults ();
		vector<Task*> getInputList();
		void clearSearchResults();
		bool executeSearchTime(Task* query);
};
#endif