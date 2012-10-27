#ifndef SORT_H
#define SORT_H
#include<vector>
#include<string>
#include "Task.h"

class Sort
{
	vector<Task*> inputList;
	string criteria;
	char order;
public:
	Sort();
	void executeSort();
	void sortByDescripAsc();
	void sortByTimeAsc();
	void sortByDescripDesc();
	void sortByTimeDesc();
	void setCriteria(string criteria);
	void setOrder(char order);
	void setInputList(vector<Task*> list);
};
#endif