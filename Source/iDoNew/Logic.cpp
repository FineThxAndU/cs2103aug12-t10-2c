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
	searchObj.executeSearchTime(userInputTask);
	introList = searchObj.getResults();
	UIObj.displayHomeScreen(introList);
	searchObj.clearSearchResults();
	while(1)
	{ 
		
	    userInput=UIObj.getUserInput();
		//assertion 1
		assert(userInput != "\0") ;
		string cmd = cmdObj.cmdProcessor(userInput, userInputTask);
		//assertion 2
		//assert(cmd != "\0") ;
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
	else if(cmd=="alternate")
		type=ALT ;
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
			    try {
				  returnVal = findToDelete(userInputTask) ;
				}
				catch(string except) {
				  UIObj.printThis(except) ;
				  returnVal = false ;
				}
				break;
		case EDIT:
				 try {
				  returnVal = findToEdit(userInputTask) ;
				}
				catch(string except) {
				  UIObj.printThis(except) ;
				  returnVal = false ;
				}
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
				  returnVal = true ;
				}
				break;
		case REDO:
			    try {
				returnVal=redoTask();
				}
				catch(string except) {
					UIObj.printThis(except) ;
				}
				break;
		case ALT:
			 returnVal = createAlternateKeyword(userInputTask) ;
			 break ;

		//case INVALID: 
				//put an exception here?
		case EXIT:
			exit(0);
	}
	return returnVal;
}

void Logic::appendToCommandList(const char * newKeyword, CommandType type)
{

 int i ; 
 switch(type) {

  case ADD:
	  for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.addList[i]))) {
			  strcpy(cmdObj.addList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.addList[i+1],"-1") ;
	  break ;
  case REMOVE:
	   for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.removeList[i]))) {
			  strcpy(cmdObj.removeList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.removeList[i+1],"-1") ;
	  break ;
  case EDIT:
	   for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.editList[i]))) {
			  strcpy(cmdObj.editList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.editList[i+1],"-1") ;
	  break ;
  case SEARCH:
	  for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.searchList[i]))) {
			  strcpy(cmdObj.searchList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.searchList[i+1],"-1") ;
	  break ;
  case UNDO:
	  for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.undoList[i]))) {
			  strcpy(cmdObj.undoList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.undoList[i+1],"-1") ;
	  break ;
  case REDO:
	   for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.redoList[i]))) {
			  strcpy(cmdObj.redoList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.redoList[i+1],"-1") ;
	  break ;
  case ALT:
	  for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.altList[i]))) {
			  strcpy(cmdObj.altList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.altList[i+1],"-1") ;
	  break ;
  case EXIT:
	  for(i=0 ; i < MAX_NO_ALTERNATES ; i++) {
		  if(!(strcmp("-1",cmdObj.exitList[i]))) {
			  strcpy(cmdObj.exitList[i],newKeyword) ;
			  break ;
		  }
	  }
	  strcpy(cmdObj.exitList[i+1],"-1") ;
	  break ;
 }

}

bool Logic::createAlternateKeyword(Task * userInputTask)
{

  bool returnVal = true ;
  Task * tempTask = new TimedTask ;
  string keyword = cmdObj.cmdProcessor(userInputTask->getDesc(), tempTask) ;
  CommandType type = determineCommand(keyword);

  //add the description of the new userInputTask to the text file (append) and also to the char array
  //NEED TO REMOVE TRAILING SPACE FROM TEMPTASK->description
  string newKeyword = cmdObj.removeLastSpace(tempTask->getDesc()) ;
  switch(type)
	{
		case ADD:
			    fileObj.setFileName("addlist.txt") ;
				fileObj.writeToFile((newKeyword.c_str())) ;
				appendToCommandList((newKeyword.c_str()), type) ;
				break;
		case REMOVE:
			    fileObj.setFileName("removelist.txt") ;
				fileObj.writeToFile(newKeyword.c_str()) ;
				appendToCommandList(newKeyword.c_str(), type) ;
				break;
		case EDIT:
			    fileObj.setFileName("editlist.txt") ;
				fileObj.writeToFile(newKeyword.c_str()) ;
				appendToCommandList(newKeyword.c_str(), type) ;
				break;
		case SEARCH:
			    fileObj.setFileName("searchlist.txt") ;
				fileObj.writeToFile(newKeyword.c_str()) ;
				appendToCommandList(newKeyword.c_str(), type) ;
				break;
		case UNDO:
			    fileObj.setFileName("undolist.txt") ;
				fileObj.writeToFile(newKeyword.c_str()) ;
				appendToCommandList(newKeyword.c_str(), type) ;
				break;
		case REDO:
			    fileObj.setFileName("redolist.txt") ;
				fileObj.writeToFile(newKeyword.c_str()) ;
				appendToCommandList(newKeyword.c_str(), type) ;
				break;
		case ALT:
			    fileObj.setFileName("altlist.txt") ;
				fileObj.writeToFile(newKeyword.c_str()) ;
				appendToCommandList(newKeyword.c_str(), type) ;
			    break ;
		case EXIT:
			    fileObj.setFileName("exitlist.txt") ;
				fileObj.writeToFile(newKeyword.c_str()) ;
				appendToCommandList(newKeyword.c_str(), type) ;
			    break ;
	}

  delete tempTask ;
  return returnVal ;

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
	taskList=sortObj.executeSort();
	//write to file
	fileObj.setTaskList(taskList);
	fileObj.writeList();
	vector<int> searchResults;
	//fileObj.setFileName("task.txt");
	//fileObj.readList();
	//Logic::taskList = fileObj.getTaskList();
	searchObj.setInputList(fileObj.getTaskList());
	//assertion
	searchObj.getIndices().size() == 0 ;
	searchObj.executeSearch(userInputTask);
	searchResults = searchObj.getIndices();
	if(searchResults.size()>1)
		setUndoStack(ADD,userInputTask,-1);
	else
		setUndoStack(ADD,userInputTask,searchResults[0]);
	searchObj.clearSearchResults();

	//return bool
	return true;
}

bool Logic::isUserIndexValid(int index, vector<int> vectorOfIndices)
{
  if(index >= 1 && index <= vectorOfIndices.size())
	  return true ;
  else 
	  return false ;

}
 
bool Logic::findToDelete(Task * userInputTask) throw(string)
{
	int i;
	//assert that the userInputTask shouldn't be null
	vector<int> searchResults;
	//fileObj.setFileName("task.txt");
	//fileObj.readList();
	//Logic::taskList = fileObj.getTaskList();
	searchObj.setInputList(fileObj.getTaskList());
    //assertion
	assert(searchObj.getIndices().size() == 0) ;
	searchObj.executeSearch(userInputTask->getDesc());
	bool returnVal = true ;
	//assertion
	
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
	//check if each userIndex is in index range of tempList, i.e. 1 to tempList.size

	for(i=0; i < userIndex.size() ; i++)
	{
	  if(isUserIndexValid(userIndex[i],userIndex)) {
	       Logic::deleteTask(searchResults[userIndex[i]-1]) ;
	}
	  else {
		  fileObj.setTaskList(Logic::taskList);
		  fileObj.writeList();
		  searchObj.clearSearchResults();
		  throw string("Invalid option chosen.") ;
	}
     		   //for now do nothing else, later get user input again after printing same list?
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

bool Logic::findToEdit(Task* userInputTask) throw (string)
{
	searchObj.setInputList(Logic::taskList);
	searchObj.executeSearch(userInputTask->getDesc());
	vector<int> searchResults = searchObj.getIndices();
	vector<Task*> tempList;
	for(int i=0;i<searchResults.size();i++)
	tempList.push_back(taskList[searchResults[i]]);
	UIObj.displayHomeScreen( tempList);
	userInput = UIObj.getUserInput();
	vector<int> userIndex = cmdObj.intProcessor(userInput) ;

	//if the other exception handling has worked
	assert(userIndex.size() != 0) ;
	for(int i=0; i < userIndex.size();i++)
	{
	 if(isUserIndexValid(userIndex[i],userIndex))	
	 {
	   Logic::editTask(searchResults[userIndex[i]-1]);
	 }
	 else 
	 { 
	    fileObj.setTaskList(Logic::taskList);
		fileObj.writeList();
		searchObj.clearSearchResults();
	    throw string("Invalid option chosen.") ;
	 }
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

bool Logic::redoTask() throw(string)
{
	CommandType redoType;
	if(redoStack.size() == 0)
	{
		throw  string("No undo to redo yet!") ;
	}
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

//spatiks

void Logic::deleteExpired()
{
	 time_t now ;
	 time(&now);
	 struct tm * currentTime = localtime(&now) ;
	 struct tm * endTimeFromFile ;
	 double timeDiff ;
	 fileObj.setFileName("task.txt") ;
	 int i = 0 ;
	
	//check end time for both deadlined and timed tasks
	for(i=0 ; i < taskList.size() ; i++)
	{
		//this bit will only work if taskList is properly sorted
		/*if(taskList[i]->getEnd() == NULL && taskList[i]->getStart() == NULL)
		{
			break ;
		}*/
	    

		if(taskList[i]->getEnd() != NULL)
		{
			endTimeFromFile = taskList[i]->getEnd() ;
			endTimeFromFile->tm_isdst = -1 ;
			endTimeFromFile->tm_wday = 0 ;
			endTimeFromFile->tm_yday = 0 ;
			endTimeFromFile->tm_year -= 1900 ;
			endTimeFromFile->tm_mon -= 1 ;
			endTimeFromFile->tm_sec = 0 ;
		    
			time_t endTime = mktime(endTimeFromFile) ;
			timeDiff = difftime(now,endTime) ;

			if((timeDiff) > 0.0) 
			{
				delete taskList[i] ;
				taskList.erase(taskList.begin()+i) ;
			}
			else
			{
			  endTimeFromFile->tm_year += 1900 ;
			  endTimeFromFile->tm_mon += 1 ;
			}
		}
	}

	fileObj.setTaskList(taskList) ;
	fileObj.writeList();
}