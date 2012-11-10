#ifndef LOGIC_H_
#define LOGIC_H_

#include<iostream>
#include<string>
#include<cstring>
#include<assert.h>
#include<exception>

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
#include <stack>

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
	
	//for findToDelete and findToEdit
	bool isUserIndexValid(int, vector<int>) ;

public:
	
	static enum CommandType{
		ADD, REMOVE, EDIT, SEARCH, UNDO,REDO,ALT,INVALID,EXIT //what happens for user command "1 2" it's not invalid, but it will determined to be in determineCommandType
	} ;
	struct Input
	{
		CommandType type;
		Task* taskObj;
		int index;
	};


	Logic();
	CommandType determineCommand(string);
    int logicMain();
	bool execute(string,Task*);
	bool addTask(Task*);
	void deleteTask(int);
	void setRedoStack(CommandType,Task*,int);

	
	bool undoTask ();
	void setUndoStack(CommandType,Task*,int);
	string getUndoStack();

	bool search(Task*);
	void editTask(int);
	bool findToDelete(Task*);
	bool findToEdit(Task*);
	bool redoTask();
	bool createAlternateKeyword(Task *) ;
	void deleteExpired() ;
	void appendToCommandList(const char *, CommandType type) ;

private:
		stack < Logic::Input> undoStack;
		stack <Input> redoStack;
		Input userStruct;
};

#endif
