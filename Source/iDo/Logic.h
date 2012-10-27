#ifndef LOGIC_H_
#define LOGIC_H_

#include<iostream>
#include<string>
#include <time.h>
#include <vector>
#include <stack>

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
#include "Command.h"



class Logic
{
	
	UI UIObj;
	string userInput;


	//this?
	CommandProcessor cmdObj;

	//actually this also no need anymore, instead vector to Command object
	Task* userInputTask ;
	

	//needs this for logicMain, Command also needs this
	Search searchObj;
	//used in ctor - no longer needed if do not need to setfileName in Logic itself
	FileIO fileObj;
	//only 'add' needs this
	Sort sortObj;

	//this??
	vector<Task*> taskList; 
	

public:


	static enum CommandType{
		ADD, REMOVE, EDIT, SEARCH, UNDO,REDO,INVALID,EXIT //what happens for user command "1 2" it's not invalid, but it will determined to be in determineCommandType
	} ;

	//this structure will be replaced by a stack of Command class objects.
	struct Input
	{
		CommandType type;
		Task* taskObj;
		int index;
	};

	Logic();
	int logicMain();
	bool execute(string,Task*);
	
	
	//this will no longer be needed?
	CommandType determineCommand(string);
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

private:
	//new architecture this becomes a stack of Command objects
		stack < Logic::Input> undoStack;
		stack <Input> redoStack;
		Input userStruct;
};

#endif
