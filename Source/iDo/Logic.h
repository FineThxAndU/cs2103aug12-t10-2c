#ifndef LOGIC_H_
#define LOGIC_H_

#include<iostream>
#include<string>

using namespace std;

#include "UI.h"
#include "Search.h"
#include "FileIO.h"
#include "Sort.h"
#include "CommandProcessor.h"
#include "Task.h"
#include "TimedTask.h"
#include "DeadlinedTask.h"
#include "FloatingTask.h"
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
	Task* userInputTask ;

public:

	static enum CommandType{
		ADD, REMOVE, EDIT, SEARCH, UNDO,INVALID,EXIT //what happens for user command "1 2" it's not invalid, but it will determined to be in determineCommandType
	} ;
	Logic();
	CommandType determineCommand(string);
    int logicMain();
	bool execute(string,Task*);
	bool addTask(Task*);
	void deleteTask(int);
	
	bool undoTask ();

	bool search(Task*);
	void editTask(int);
	bool findToDelete(Task*);
	bool findToEdit(Task*);
	;
};

#endif
