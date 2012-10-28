#include "AddCommand.h"


bool AddCommand::execute(vector<Task*> tasksInSchedule, UI accessToUI)
{
	
	fileHandler.setFileName("task.txt");

	vector<Task*>::iterator it ;

	it = tasksInSchedule.begin() ;

	tasksInSchedule.push_back((*(it)));


	//sort the taskList using sort obj
	sorter.setInputList(tasksInSchedule);
	sorter.executeSort();
	//write to file
	
	fileHandler.setTaskList(tasksInSchedule);
	fileHandler.writeList();
	
	/*
	vector<int> searchResults;
	
	searcher.setInputList(fileHandler.getTaskList());
	searcher.executeSearch((*(it)));
	searchResults=searcher.getIndices();

	
	if(searchResults.size() > 1)
		setUndoStack(ADD,userInputTask,-1);
	else
		setUndoStack(ADD,userInputTask,searchResults[0]);
	searchObj.clearSearchResults();
	*/

	
	return true ;
}



