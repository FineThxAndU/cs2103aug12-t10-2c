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

	static enum CommandType {
		ADD, REMOVE, EDIT, SEARCH, UNDO, REDO, ALT, INVALID, EXIT 
	} ;


	
	//for findToDelete and findToEdit
	bool isUserIndexValid(int, vector<int>) ;

	static const string FILENAME_ADD_ALTERNATES ;
	static const string FILENAME_REMOVE_ALTERNATES ;
	static const string FILENAME_EDIT_ALTERNATES ;
	static const string FILENAME_EXIT_ALTERNATES ;
	static const string FILENAME_SEARCH_ALTERNATES ;
	static const string FILENAME_ALTERNATE_ALTERNATES ;
	static const string FILENAME_UNDO_ALTERNATES ;
	static const string FILENAME_REDO_ALTERNATES ;

public:
	

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
	void deleteExpiredTasks() ;

	
private:
		stack < Logic::Input> undoStack;
		stack <Input> redoStack;
		Input userStruct;
};

#endif
