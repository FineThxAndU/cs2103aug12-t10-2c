#ifndef UI_H_
#define UI_H_

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include "Task.h" 

using namespace std ;

class UI
{
 
private:
	
	string userInput ;
	void placeCursorAt(const int, const int) ;
	void makeConvertibleToString(tm * timePointer) ;
	void changeBackTimePointer(tm *) ;
	void displayTimedTasks(tm * &, tm * &, string, int taskNo) ;
	void displayDeadlineTasks(tm * &, string, int taskNo) ;
	COORD currentCursor ;

	
	static const int TABLE_START_POSITION_X = 2 ;
	static const int TABLE_START_POSITION_Y = 4 ;
	static const string TABLE_FIELDS ;

	static const string MESSAGE_NEXT_COMMAND ;
	static const string MESSAGE_WELCOME ; 
	static const string MESSAGE_HELP ;
	static const string MESSAGE_INVALID ;

	static const string MESSAGE_ALTERNATE_SUCCESS ; 
	static const string MESSAGE_ALTERNATE_FAIL ;

	static const string MESSAGE_ADDED ;
	static const string MESSAGE_INVALID_ADD ;

	static const string MESSAGE_DELETED ;
	static const string MESSAGE_INVALID_DELETE ;

	static const string MESSAGE_EDITED ;
	static const string MESSAGE_INVALID_EDIT ;

	static const string MESSAGE_SEARCH_SUCCESS ;
	static const string MESSAGE_INVALID_SEARCH ;

	static const string MESSAGE_EXIT ;
	static const string MESSAGE_UNDONE ;
	static const string MESSAGE_UNDO_FAIL ;

 public:

	void displayHomeScreen(vector<Task*>) ; 

	void feedback(bool, string command) ;

	void displayTrueFeedback(string command) ;

	void displayFalseFeedback(string command) ;

	void printThis(string) ;
	
	string getUserInput() ;

} ;

#endif 