#ifndef EDIT_H
#define EDIT_H

#include "Command.h"
#include "CommandProcessor.h"

class EditCommand : public Command

{
	//inherits sorter, fileHandler, and tasksInvolved
	
	 
public:

	virtual bool execute(vector<Task*> tasksInSchedule, UI) ;
	virtual bool undo(

} ;


#endif 