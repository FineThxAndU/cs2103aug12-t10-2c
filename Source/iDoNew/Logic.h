#ifndef LOGIC_H_
#define LOGIC_H_

#include <iostream>
#include <string>
#include <cstring>
#include <assert.h>
#include <exception>
#include <time.h>
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


class Logic
{
	static const string TASK_FILE_NAME;
	UI UIObj;
	Search searchObj;
	FileIO fileObj;
	Sort sortObj;
	vector<Task*> taskList; 
	string userInput;
	CommandProcessor cmdObj;
	Task* userInputTask, *userInputNewTask ;

	static enum CommandType {
		ADD, REMOVE, EDIT, SEARCH, UNDO, REDO, ALT, EXIT 
	} ;

	static const string FILENAME_ADD_ALTERNATES ;
	static const string FILENAME_REMOVE_ALTERNATES ;
	static const string FILENAME_EDIT_ALTERNATES ;
	static const string FILENAME_EXIT_ALTERNATES ;
	static const string FILENAME_SEARCH_ALTERNATES ;
	static const string FILENAME_ALTERNATE_ALTERNATES ;
	static const string FILENAME_UNDO_ALTERNATES ;
	static const string FILENAME_REDO_ALTERNATES ;
	static const int MAX_KEYWORD_SIZE = 100 ;

	struct Input
	{
		CommandType type;
		Task* taskObj;
		int index;
	};

	//
	stack < Logic::Input> undoStack;
	//
	stack <Input> redoStack;
	//
	Input userStruct;

        bool execute(string,Task*, Task*);
	CommandType determineCommand(string);

	void deleteExpiredTasks() ;
	
	void setRedoStack(CommandType,Task*,int);
	void setUndoStack(CommandType,Task*,int);
	string getUndoStack();

	tm* getCurrentTime();
	void updateHomeScreen();
	//
	void updateTaskFile();
	//
	void setSearchObj(Task*);
	//void updateSearchResults();

public:
	Logic();
	int logicMain();
        
	bool addTask(Task*);
	bool search(Task*);
	void editTask(int);
	bool findToDelete(Task*);
	void deleteTask(int);
	bool findToEdit(Task*, Task*);


	bool createAlternateKeyword(Task *) ;	

	bool isUserIndexValid(int, vector<int>) ;
	
	bool undoTask ();
	bool redoTask();
};

#endif
