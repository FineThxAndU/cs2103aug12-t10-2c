#ifndef UI_H_
#define UI_H_

#include <iostream>
#include <string>
#include "Task.h" 
#include <vector>
#include <iomanip>
#include <Windows.h>

using namespace std ;



class UI
{
 
private:
	
	string userInput ;
	void placeCursorAt(const int, const int) ;
	COORD currentCursor ;
	
	//switch back to white after printing 
	//not implemented yet
	void printInColor() ;

	static const int TABLE_START_POSITION_X = 2 ;
	static const int TABLE_START_POSITION_Y = 4 ;
	static const string TABLE_FIELDS ;

	static const string MESSAGE_NEXT_COMMAND ;
	static const string MESSAGE_WELCOME ; 
	static const string MESSAGE_HELP ;
	static const string MESSAGE_INVALID ;

	static const string MESSAGE_ADDED ;
	static const string MESSAGE_INVALID_ADD ;

	static const string MESSAGE_DELETED ;
	static const string MESSAGE_INVALID_DELETE ;

	static const string MESSAGE_EDITED ;
	//static const string MESSAGE_INVALID_EDIT ;

	static const string MESSAGE_SEARCH_SUCCESS ;
	static const string MESSAGE_INVALID_SEARCH ;

	static const string MESSAGE_EXIT ;
   
 public:

	void displayHomeScreen(vector<Task*>) ; 

	//this one is not yet implemented
	void displayFloatingTasks(vector<Task*>) ;

	void feedback(bool, string command) ;
	
	//to be implemented later - for now all feedback in feedback function

	//void addFeedback(bool) 
	//void deleteFeedback(bool) 
	//void editFeedback(bool) 
	//void searchFeedback(bool) 
	//void undoFeedback(bool) 
	
	string getUserInput() ;

} ;

#endif 