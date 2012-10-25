#ifndef FILEIO_H
#define FILEIO_H
#include "Task.h"
#include <vector>
#include <fstream>

class FileIO
{
	string fileName;
	vector<Task*> taskList;
public:
	void setFileName(string flieName);
	void setTaskList(vector<Task*>& list);
	void readList();
	void writeList();
	vector<Task*> getTaskList();

};
#endif