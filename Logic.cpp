#include <iostream>
#include <string>
#include "Logic.h"
#include <time.h>

int Logic::logicMain()
{
	time_t now;
	struct tm *current;
	now = time(0);
	current = localtime(&now);
	taskList=searchObj.search (current);
	UIObj.displayHomeScreen(taskList);
	while(1)
	{
		userInput=UIObj.getUserInput();
		string cmd=cmdObj.cmdProcessor(userInput, userInputTask);
		
		bool returnVal=Logic::execute(cmd,userInputTask);
		UIObj.feedback(returnVal,cmd);
	}

	return 0;
}

Logic::CommandType Logic::determineCommand(string cmd)
{
	Logic::CommandType type;
	if(cmd=="add")
		type=ADD;
	else
		if(cmd=="delete")
			type=DELETE;
		else
			if(cmd=="search")
				type=SEARCH;
			else
				if(cmd=="edit")
					type=EDIT;
				else
					if(cmd=="undo")
						type=UNDO;
	return type;
}

bool Logic::execute(string cmd,Task* userInputTask)
{
	CommandType type=Logic::determineCommand(cmd);
	bool returnVal;
	switch(type)
	{
		case ADD:
				returnVal=addTask(userInputTask);
				break;
		case DELETE:
				returnVal=deleteTask(userInputTask);
				break;
		case EDIT:
				returnVal=editTask(userInputTask);
				break;
		case SEARCH:
				returnVal=searchObj.search(userInputTask);
				break;
		case UNDO:
				returnVal=undoTask();
				break;
	}
	return returnVal;
}

bool Logic::addTask(Task* userInputTask)
{

	//setfile name to tasks.t
	fileObj.setFileName("task.txt");
	//get list of task* from file
	taskList=fileObj.returnTasks();
	//append userInputTask to the list returned from fileObj 
	taskList.push_back(userInputTask);
	//sort that taskList using sort obj
	sortObj.sort(taskList);
	//write to file
	fileObj.writeTasks(taskList);
	//return bool
	return true;
}

bool Logic::findToDelete(Task * userInputTask)
{
	//task has JUST description 
	//based on description, use search obj to retrieve vector list of matching tasks
	vector<int> searchResults;
	searchResults=searchObj.getindices(userInputTask->getDesc());
	vector<Task*> tempList;
	for(int i=0;i<searchResults.size();i++)
	tempList.push_back(taskList[searchResults[i]]);
	UIObj.displayHomeScreen( tempList);
	userInput=UIObj.getUserInput();
	vector<int> userIndex= cmdObj.intProcessor(userInput);
	for(int i=0;i<userIndex.size();i++)
	{
		Logic::deleteTask(searchResults[userIndex[i]-1]);
	}
	return true;
	//getUserInput() and call intProcessor of command processor
	//now u have int vector use that to find matching task * from retrieved list (from search)
	//matching task * shld be deleted (find a vector function that does the shifting as well)
	//


}

void Logic::deleteTask(int index)
{
	delete [] taskList[index];
	taskList.erase(taskList.begin()+index);
}
	