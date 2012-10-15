#ifndef FLOATING_H
#define FLOATING_H
#include "Task.h"

class FloatingTask : public Task
{
public:
	FloatingTask();
	string getDesc();
	tm* getStart();
	tm* getEnd();
	void setDesc(string desc);
	void setStart(tm* start);
	void setEnd(tm* end);
	bool FloatingTask::operator==(Task* t1);
	void operator=(Task* t1);
};
#endif