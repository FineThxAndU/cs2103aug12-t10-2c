#ifndef ADD_H
#define ADD_H

#include "Command.h"
#include "Sort.h"


class AddCommand : public Command
{

	Sort sorter ;

public:

	virtual bool execute(vector<Task*>, UI) ;
	virtual bool undo(vector<Task*>, UI) ;

} ;


#endif