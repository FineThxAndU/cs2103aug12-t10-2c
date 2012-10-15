#include<iostream>
#include<string>
using namespace std;
#include "UI.h"
#include "Search.h"
#include "FileIO.h"
#include "Sort.h"
#include "CommandProcessor.h"
#include "task.h"
#include <time.h>
#include <vector>

class Logic
{
	UI UIObj;
	Search searchObj;
	FileIO fileObj;
	Sort sortObj;
	vector<Task*> taskList; 
	string userInput;
	CommandProcessor cmdObj;
	Task * userInputTask ;


public:
	static enum CommandType
	{
		ADD, DELETE, EDIT, SEARCH, UNDO
	};
	Logic::CommandType determineCommand(string);
	int logicMain ();
	bool execute (string,Task*);
	bool addTask (Task*);
	void deleteTask (int);
	bool undoTask ();
	void search(tm*);
	void log();
	bool editTask(Task*);
	bool findToDelete(Task*);
	void findToEdit();
};

