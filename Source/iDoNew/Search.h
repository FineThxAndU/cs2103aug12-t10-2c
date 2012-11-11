#ifndef SEARCH_H
#define SEARCH_H
#include "Task.h"
#include <string>
#include <vector>
#include <time.h>
#include <assert.h>
#include <exception>

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
		void makeConvertible(tm*);
		void formatHourYear(tm*);
		void revertToOriginalTime( tm *time, int hour);
};
#endif