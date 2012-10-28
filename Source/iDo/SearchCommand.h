#ifndef SEARCHCOMMAND_H
#define SEARCHCOMMAND_H


#include "Command.h"

class SearchCommand : public Command
{


public:

	virtual bool execute(vector<Task*>, UI) ;
	virtual bool undo() ;

} ;


#endif