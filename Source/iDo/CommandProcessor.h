#ifndef COMMAND_H_
#define COMMAND_H_

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "Task.h"

using namespace std;

class CommandProcessor
{

public:

	vector<int> intProcessor (string);
	string cmdProcessor (string, Task*& );
	void descProcessor (string, Task*& );
	tm* stringToTime (string);
} ;


#endif