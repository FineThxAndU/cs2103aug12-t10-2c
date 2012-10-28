#include "EditCommand.h"

bool EditCommand::execute(vector<Task*> tasksInSchedule)
{

	searcher.setInputList(tasksInSchedule);

	vector<Task*>::iterator itToBeginning = tasksInvolved.begin() ;

	//lets assume user enters full description followed by the new date and time with start and end tags 
	searcher.executeSearch((*itToBeginning)->getDesc());
	vector<int> searchResults = searcher.getIndices();

	userInput=UIObj.getUserInput() ;
	userInputTask = taskList[index] ;
	cmdObj.descProcessor(userInput,userInputTask) ;
	setUndoStack(EDIT,taskList[index],index) ;
	delete taskList[index] ;
	taskList[index]=userInputTask ;

	
	fileHandler.setTaskList(tasksInSchedule);
	fileHandler.writeList();

	searcher.clearSearchResults();
	

	//and then edit function


	return true ;

}