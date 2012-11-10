#ifndef FILEIO_H
#define FILEIO_H
#include "Task.h"
#include <vector>
#include <fstream>
#include <sstream>

class FileIO
{
	string fileName;
	vector<Task*> taskList;
	static const int MAX_CHAR_IN_LINE = 80 ;
	static const int MAX_NO_LINES = 100 ;
	string convertToString(char * name) ;

public:
	void setFileName(string fileName);
	void setTaskList(vector<Task*>& list);
	void readList();
	void writeList();
	vector<Task*> getTaskList();

	//spatiks
	void writeToFile(const char *) ;
	//by reference
	vector<string> readFromFile() ;

};
#endif