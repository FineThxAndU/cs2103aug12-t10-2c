#include "stdafx.h"
#include "Logic.h"
Logic::Logic()
{
	fileObj.setFileName("task.txt");
	fileObj.readList();
	taskList=fileObj.getTaskList();
	while(!undoStack.empty())
	{
		undoStack.pop() ;
	}

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
	searchObj.clearSearchResults();
	while(1)
	{
		userInput=UIObj.getUserInput();
		//assertion 1
		assert(userInput != "\0") ;
		string cmd=cmdObj.cmdProcessor(userInput, userInputTask);
		//assertion 2
		assert(cmd != "\0") ;
		bool returnVal;
		returnVal = Logic::execute(cmd,userInputTask);
		//assertion 3
		assert(returnVal == true || returnVal == false) ;
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
	else if(cmd=="redo")
		type=REDO;
	else if(cmd=="exit")
		type=EXIT;
	//but type is never invalid because if it is not any of the above, it is made 'add' command automatically.
	else
		type=INVALID ;
	//can put an exception here for invalid type
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
				returnVal = findToDelete(userInputTask) ;
				break;
		case EDIT:
				returnVal=findToEdit(userInputTask);
				break;
		case SEARCH:
				returnVal=Logic::search(userInputTask);
				break;
		case UNDO:
				try {
				returnVal=undoTask();
				}
				catch(string except) {
				UIObj.printThis(except) ;
				//cout << except ;
				returnVal = true ;
				}
				break;
		case REDO:
				returnVal=redoTask();
				break;
		case INVALID: 
				//put an exception here?
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

//	setUndoStack(ADD,userInputTask,-1);
	//sort that taskList using sort obj
	sortObj.setInputList(taskList);
	sortObj.executeSort();
	//write to file
	fileObj.setTaskList(taskList);
	fileObj.writeList();
	vector<int> searchResults;
	//fileObj.setFileName("task.txt");
	//fileObj.readList();
	//Logic::taskList = fileObj.getTaskList();
	searchObj.setInputList(fileObj.getTaskList());
	searchObj.executeSearch(userInputTask);
	searchResults=searchObj.getIndices();
	if(searchResults.size()>1)
		setUndoStack(ADD,userInputTask,-1);
	else
		setUndoStack(ADD,userInputTask,searchResults[0]);
	searchObj.clearSearchResults();

	//return bool
	return true;
}
 
bool Logic::findToDelete(Task * userInputTask) 
{
	int i;
	
	vector<int> searchResults;
	//fileObj.setFileName("task.txt");
	//fileObj.readList();
	//Logic::taskList = fileObj.getTaskList();
	searchObj.setInputList(fileObj.getTaskList());
	searchObj.executeSearch(userInputTask->getDesc());
	bool returnVal = true ;

	searchResults = searchObj.getIndices(); //returns the indices of matches corresponding to MAIN taskList
	if(searchResults.size() == 0)
	{
		returnVal = false ;
		return returnVal ;
	}
	
	vector<Task*> tempList ;
	
	for(i=0 ; i < searchResults.size() ; i++)
	{
		tempList.push_back(taskList[searchResults[i]]);
	}

	UIObj.displayHomeScreen(tempList);
	userInput=UIObj.getUserInput();

	vector<int> userIndex = cmdObj.intProcessor(userInput);

	for(i=0; i < userIndex.size() ; i++)
	{
		Logic::deleteTask(searchResults[userIndex[i]-1]);
	}

	fileObj.setTaskList(taskList);
	fileObj.writeList();
	searchObj.clearSearchResults();
	returnVal = true ;
	return returnVal ;

}

void Logic::deleteTask(int index)
{
	setUndoStack(REMOVE,taskList[index],index);
	delete taskList[index];
	taskList.erase(taskList.begin()+index);
}
	
bool Logic::search(Task* userInputTask)
{
	searchObj.setInputList(Logic::taskList);
	searchObj.executeSearch(userInputTask->getDesc());
	vector<Task*> searchResults=searchObj.getResults();
	UIObj.displayHomeScreen(searchResults);
	searchObj.clearSearchResults();
	return true;

}

bool Logic::findToEdit(Task* userInputTask)
{
	searchObj.setInputList(Logic::taskList);
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
	searchObj.clearSearchResults();
	return true;
}

void Logic::editTask(int index)
{
	userInput=UIObj.getUserInput();
	userInputTask = taskList[index];
	cmdObj.descProcessor(userInput,userInputTask);
	setUndoStack(EDIT,taskList[index],index);
	delete taskList[index];
	taskList[index]=userInputTask;
}
	

bool Logic::undoTask () throw(string)
{
	CommandType undoType;

	if(undoStack.size() == 0)
	{
		throw  string("No commands to undo yet!") ;
	}
	undoType=Logic::undoStack.top().type;
	userInputTask=undoStack.top().taskObj;
	int index= undoStack.top().index;
	Task* newtask= new TimedTask;
	setRedoStack(undoType,userInputTask,index);
	Logic::undoStack.pop();
	bool returnVal;

	switch(undoType)
	{
		case ADD:
				if(index==-1)
					returnVal=false;
				else
					deleteTask(index);
					undoStack.pop();
					fileObj.setTaskList(taskList);
					fileObj.writeList();
					searchObj.clearSearchResults();
					returnVal=true;
					break;
		case REMOVE:
				returnVal=addTask(userInputTask);
				undoStack.pop();
				break;
		case EDIT:
				delete taskList[index];
				taskList[index]=userInputTask;
				fileObj.setTaskList(taskList);
				fileObj.writeList();
				searchObj.clearSearchResults();
				returnVal=true;
				break;
		default:
				returnVal= false;
			
	}
	return returnVal;
}

void Logic::setUndoStack(CommandType type,Task* tempTask,int index)
{
	Task* newTask= new TimedTask;
	newTask->setDesc(tempTask->getDesc());
	newTask->setEnd(tempTask->getEnd());
	newTask->setStart(tempTask->getStart());
	userStruct.type=type;
	userStruct.taskObj=newTask;
	userStruct.index=index;
	undoStack.push(userStruct);
}
void Logic::setRedoStack(CommandType type,Task* tempTask,int index)
{
	Task* newTask= new TimedTask;
	newTask->setDesc(tempTask->getDesc());
	newTask->setEnd(tempTask->getEnd());
	newTask->setStart(tempTask->getStart());
	userStruct.type=type;
	userStruct.taskObj=newTask;
	userStruct.index=index;
	redoStack.push(userStruct);
}
bool Logic::redoTask()
{
	CommandType redoType;
	redoType=Logic::redoStack.top().type;
	userInputTask=redoStack.top().taskObj;
	int index= redoStack.top().index;
	Logic::redoStack.pop();
	bool returnVal;
	switch(redoType)
	{
		case ADD: 
				returnVal=addTask(userInputTask);
				undoStack.pop();
				break;
		case REMOVE:
				deleteTask(index);
				undoStack.pop();
				fileObj.setTaskList(taskList);
				fileObj.writeList();
				searchObj.clearSearchResults();
				returnVal=true;
				break;
		case EDIT:
				delete taskList[index];
				taskList[index]=userInputTask;
				fileObj.setTaskList(taskList);
				fileObj.writeList();
				searchObj.clearSearchResults();
				returnVal=true;
				break;
		default: returnVal=false;
	}
	return returnVal;
}
