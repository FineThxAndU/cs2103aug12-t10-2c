#ifndef DELETE_H
#define DELETE_H

#include "Command.h"

class DeleteCommand: public Command
{


public :

	virtual bool execute(vector<Task*>, UI) ;
	virtual bool undo(vector<Task*>) ;


} ;

#endif