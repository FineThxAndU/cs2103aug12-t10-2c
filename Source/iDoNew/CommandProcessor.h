//Parser class

#ifndef COMMAND_H_
#define COMMAND_H_

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <assert.h>
#include <ctype.h>

#include "DeadlinedTask.h"
#include "FloatingTask.h"
#include "TimedTask.h"
#include "Task.h"
#include "FileIO.h"

using namespace std;

static int const ASCII_VALUE_0 = 48;
const int MAX_COMMAND_SIZE = 100 , MAX_TIME_SIZE = 100, MAX_DESC_SIZE = 100, MAX_WORD_SIZE = 100, MAX_NO_ALTERNATES = 100 , MAX_INPUT_SIZE = 100  ;

const char startList[][MAX_COMMAND_SIZE] = {"s", "st", "sta", "star", "start","b", "be", "beg", "begi", "begin", "-1"};
const char endList[][MAX_COMMAND_SIZE] = {"e", "en", "end", "-1"};
const char timeList[][MAX_COMMAND_SIZE] = {"day","after","today", "tomorrow","before","yesterday", "next" , "am" , "pm", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday","th", "st","nd","coming","week","month","year","January","February","March","April","May","June","July","August","September","October","November","December","now", "-1"};
const char monthList[][MAX_COMMAND_SIZE]  = {"January","February","March","April","May","June","July","August","September","October","November","December", "-1"};
const char days[][MAX_COMMAND_SIZE] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "-1"};

class CommandProcessor
{

private:

	FileIO fileObject ;

	//to load alternates for command keywords into respective char arrays
	void initAddList() ;
	void initRemoveList() ;
	void initEditList() ;
	void initSearchList() ;
    void initUndoList() ;
    void initExitList() ;
	void initRedoList() ;
	void initAltList() ;

	//lists of alternate commands for keywords
	char addList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;
	char removeList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;
	char editList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;
	char searchList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;
	char undoList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;
	char exitList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;
	char redoList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;
	char altList[MAX_NO_ALTERNATES][MAX_COMMAND_SIZE] ;

	
	static const string FILENAME_ADD_ALTERNATES ;
	static const string FILENAME_REMOVE_ALTERNATES ;
	static const string FILENAME_EDIT_ALTERNATES ;
	static const string FILENAME_EXIT_ALTERNATES ;
	static const string FILENAME_SEARCH_ALTERNATES ;
	static const string FILENAME_ALTERNATE_ALTERNATES ;
	static const string FILENAME_UNDO_ALTERNATES ;
	static const string FILENAME_REDO_ALTERNATES ;


public:

	CommandProcessor() ;
	vector<int> intProcessor (string);
	string cmdProcessor (string, Task*& );
	void descProcessor (string, Task*& );
	tm* stringToTime (string);
	bool actualKeyWord(char userCmd[MAX_COMMAND_SIZE]);
	//overloaded isFound
	bool isFound(char cmd[MAX_COMMAND_SIZE], string cmdType);
	bool isFound(char cmd[MAX_COMMAND_SIZE], const char [][MAX_COMMAND_SIZE]);

	bool isStart(char singleWord[MAX_COMMAND_SIZE]);
	bool isEnd(char singleWord[MAX_COMMAND_SIZE]);
	bool isDateTime(char singleWord[MAX_COMMAND_SIZE]);
	bool isNumericalTime(char singleWord[MAX_COMMAND_SIZE]);
	void trim(char word[MAX_COMMAND_SIZE]);
	string removeLastSpace(string) ;
	bool isDay(int input);
	bool isMonth(int input);
	bool isYear(int input);
	bool isHour(int input);
	bool isMinute(int input);
	bool parseDateTime(char dateTime[MAX_TIME_SIZE]);
	void convertDate(char Date[MAX_TIME_SIZE]);
	void convertTime(char Date[MAX_TIME_SIZE]);
	void addZeroes(char Date[MAX_TIME_SIZE]);
	bool isDate(int first, int second, int third );
	bool isTime(int first, int second, int third );
	void splitTime(char singleWord[MAX_COMMAND_SIZE], int &first, int &second, int&third);
	void parseCharTime(char singleWord[MAX_WORD_SIZE], char finalTime[MAX_TIME_SIZE]);
	tm evaluateDate(char day[MAX_TIME_SIZE], char finalTime[MAX_TIME_SIZE]);
	tm evaluateMonth(char month[MAX_TIME_SIZE], char finalTime[MAX_TIME_SIZE]);
	void incrementDate(tm *date, int days);
	void incrementMonth(tm *date, int months);
	void incrementYear(tm *date, int years);
	bool isLeapYear(int year);
	void dateToString(tm *date, char finalDate[MAX_TIME_SIZE]);
	void deleteConsecSpaces(char input[MAX_INPUT_SIZE]);

	//to add new keyword to private alternates list, called in Logic.cpp
	//needed to have function for each type, as passing 2D char array as parameter was unpredictable
	void appendToAddList(const char *) ;
	void appendToRemoveList(const char *) ;
	void appendToEditList(const char *) ;
	void appendToSearchList(const char *) ;
	void appendToUndoList(const char *) ;
	void appendToRedoList(const char *) ;
	void appendToAltList(const char *) ;
	void appendToExitList(const char *) ;

} ;


#endif