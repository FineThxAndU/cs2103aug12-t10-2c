#ifndef COMMAND_H_
#define COMMAND_H_

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "Task.h"

using namespace std;

static int const ASCII_VALUE_0 = 48;
const int MAX_COMMAND_SIZE = 100 , MAX_TIME_SIZE = 100, MAX_DESC_SIZE = 100;
const char addList[][MAX_COMMAND_SIZE] = {"add" , "ad" , "a", "-1"};
const char removeList[][MAX_COMMAND_SIZE] = { "del", "de", "delet", "dele", "delete", "re", "rem", "remo","remov", "remove",  "-1"};
const char editList[][MAX_COMMAND_SIZE] =  {"ed", "edi", "edit", "mo", "mod", "modi", "modif", "modify", "-1"};
const char searchList[][MAX_COMMAND_SIZE] = {"se", "sea", "sear", "searc", "search", "fi", "fin", "find","ge", "get", "-1"};
const char undoList[][MAX_COMMAND_SIZE] = {"un", "und", "undo", "-1"};
const char exitList[][MAX_COMMAND_SIZE] = { "esc","ex", "exi", "exit","qu","qui","quit", "-1"};

class CommandProcessor
{

public:

	vector<int> intProcessor (string);
	string cmdProcessor (string, Task*& );
	void descProcessor (string, Task*& );
	tm* stringToTime (string);
	bool actualKeyWord(char userCmd[MAX_COMMAND_SIZE]);
	bool isFound(char cmd[MAX_COMMAND_SIZE], const char cmdList[][MAX_COMMAND_SIZE]);
} ;


#endif