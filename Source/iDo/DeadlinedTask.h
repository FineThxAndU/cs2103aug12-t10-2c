#ifndef DEADLINED_H
#define DADLINED_H
#include "Task.h"

class DeadlinedTask :public Task
{
public:
	DeadlinedTask();
	string getDesc();
	tm* getStart();
	tm* getEnd();
	void setDesc(string desc);
	void setStart(tm* start);
	void setEnd(tm* end);
	bool DeadlinedTask::operator==(Task* t1);
	void operator=(Task* t1);
};
#endif