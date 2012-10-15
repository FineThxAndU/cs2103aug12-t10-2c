 #include "Logic.h"
Logic::Logic()
{
	fileObj.setFileName("task.txt");
	fileObj.readList();
	taskList=fileObj.getTaskList();

}


int Logic::logicMain()
{
	vector<Task*> introList;
	time_t now;
	struct tm *current;
	time(&now);
	current = localtime(&now);
	userInputTask = new TimedTask;
	userInputTask->setStart(current);
	searchObj.setInputList(taskList);
	searchObj.executeSearch(userInputTask);
	introList = searchObj.getResults();
	UIObj.displayHomeScreen(introList);

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
	else if(cmd=="delete")
		type=REMOVE;
	else if(cmd=="search")
		type=SEARCH;
	else if(cmd=="edit")
		type=EDIT;
	else if(cmd=="undo")
		type=UNDO;
	else if(cmd=="exit")
		type=EXIT;
	//NEED ONE MORE TYPE for the follow up user input to delete i.e. string "1 2" 
	else
		type=INVALID ;
	return type;
}

bool Logic::execute(string cmd,Task* userInputTask)
{
	CommandType type=Logic::determineCommand(cmd);
	bool returnVal = false;
	switch(type)
	{
		case ADD:
				returnVal=addTask(userInputTask);
				break;
		case REMOVE:
				returnVal=findToDelete(userInputTask);
				break;
		case EDIT:
				returnVal=findToEdit(userInputTask);
				break;
		case SEARCH:
				returnVal=Logic::search(userInputTask);
				break;
		case UNDO:
				returnVal=undoTask();
				break;
		case EXIT:
			exit(0);
	}
	return returnVal;
}

bool Logic::addTask(Task* userInputTask)
{

	//setfile name to tasks.t
	fileObj.setFileName("task.txt");
	//get list of task* from file
	//taskList = fileObj.getTaskList();
	//append userInputTask to the list returned from fileObj 
	taskList.push_back(userInputTask);
	//sort that taskList using sort obj
	sortObj.setInputList(taskList);
	sortObj.executeSort();
	//write to file
	fileObj.setTaskList(taskList);
	fileObj.writeList();
	//return bool
	return true;
}

bool Logic::findToDelete(Task * userInputTask)
{
	int i;
	//task has JUST description 
	//based on description, use search obj to retrieve vector list of matching tasks
	vector<int> searchResults;
	//fileObj.setFileName("task.txt");
	//fileObj.readList();
	//Logic::taskList = fileObj.getTaskList();
	searchObj.setInputList(fileObj.getTaskList());
	searchObj.executeSearch(userInputTask->getDesc());
	searchResults=searchObj.getIndices();
	vector<Task*> tempList;
	for(i=0;i<searchResults.size();i++)
	tempList.push_back(taskList[searchResults[i]]);
	UIObj.displayHomeScreen(tempList);
	userInput=UIObj.getUserInput();
	vector<int> userIndex= cmdObj.intProcessor(userInput);

	for(i=0;i<userIndex.size();i++)
	{
		Logic::deleteTask(searchResults[userIndex[i]-1]);
	}
	fileObj.setTaskList(taskList);
	fileObj.writeList();
	return true;
	//getUserInput() and call intProcessor of command processor
	//now u have int vector use that to find matching task * from retrieved list (from search)
	//matching task * shld be deleted (find a vector function that does the shifting as well)
	//


}

void Logic::deleteTask(int index)
{
	delete taskList[index];
	taskList.erase(taskList.begin()+index);
}
	
bool Logic::search(Task* userInputTask)
{
	searchObj.setInputList(Logic::taskList);
	searchObj.executeSearch(userInputTask->getDesc());
	vector<Task*> searchResults=searchObj.getResults();
	UIObj.displayHomeScreen(searchResults);
	return true;

}

bool Logic::findToEdit(Task* userInputTask)
{
	searchObj.executeSearch(userInputTask->getDesc());
	vector<int> searchResults= searchObj.getIndices();
	vector<Task*> tempList;
	for(int i=0;i<searchResults.size();i++)
	tempList.push_back(taskList[searchResults[i]]);
	UIObj.displayHomeScreen( tempList);
	userInput=UIObj.getUserInput();
	vector<int> userIndex= cmdObj.intProcessor(userInput);
	for(int i=0;i<userIndex.size();i++)
	{
		Logic::editTask(searchResults[userIndex[i]-1]);
	}
	fileObj.setTaskList(Logic::taskList);
	fileObj.writeList();
	return true;
}

void Logic::editTask(int index)
{
	userInput=UIObj.getUserInput();
	cmdObj.descProcessor(userInput,userInputTask);
	delete taskList[index];
	taskList[index]=userInputTask;
}
	

bool Logic::undoTask (){

	return false;
}
