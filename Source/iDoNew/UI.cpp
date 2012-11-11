#include "UI.h"

const string UI::MESSAGE_NEXT_COMMAND = "Enter Command: " ;
const string UI::MESSAGE_WELCOME = "\t\t\t\t ****iDo****" ;

const string UI::MESSAGE_HELP = "Valid Commands: add, delete, search, edit, undo, redo, alternate, exit." ;
const string UI::MESSAGE_INVALID = "Invalid command entered!" ;

const string UI::TABLE_FIELDS = "No.  Task Description\t\t\t  From/At\t\tTo\t\t" ;

//const string UI::MESSAGE_EMPTY = "\niDo is empty! No tasks added yet." ;

const string UI::MESSAGE_ALTERNATE_SUCCESS = "Successfully added alternate keyword." ;
const string UI::MESSAGE_ALTERNATE_FAIL = "Unable to add alternate to keyword." ;

const string UI::MESSAGE_ADDED =  "Successfully added task to schedule." ;
const string UI::MESSAGE_INVALID_ADD = "Unable to add task to schedule." ;

const string UI::MESSAGE_DELETED = "Deleted task(s) from schedule." ;
const string UI::MESSAGE_INVALID_DELETE = "Unable to delete/Task(s) matching entered description not found." ;

const string UI::MESSAGE_EDITED = "Edited task in schedule." ;
const string UI::MESSAGE_INVALID_EDIT = "Unable to edit/Task(s) matching entered description not found." ;

const string UI::MESSAGE_SEARCH_SUCCESS = "The above tasks matched the entered description." ;
const string UI::MESSAGE_INVALID_SEARCH = "No tasks matching the entered description were found!" ; 

const string UI::MESSAGE_EXIT = "Exiting iDo now." ;
const string UI::MESSAGE_UNDONE = "Command successfully undone." ;
const string UI::MESSAGE_UNDO_FAIL = "Undo not possible." ;

void UI::makeConvertibleToString(tm * timePointer) {
	
	timePointer->tm_year -= 1900;
	timePointer->tm_mon -= 1;
	timePointer->tm_isdst = -1;
	timePointer->tm_wday = 0;
	timePointer->tm_yday = 0;
	timePointer->tm_sec = 0;

}

void UI::changeBackTimePointer(tm * timePointer) {

	timePointer->tm_mon += 1;
    timePointer->tm_year += 1900;

}


void UI::displayTimedTasks(tm * & startTime, tm * & endTime, string description, int taskNo) {

	makeConvertibleToString(startTime) ;
	makeConvertibleToString(endTime) ;
	cout << taskNo << "\t" << description << setw(17) ;
	cout << asctime(startTime) << asctime(endTime) ;
    changeBackTimePointer(startTime) ;
	changeBackTimePointer(endTime) ;

}

void UI::displayDeadlineTasks(tm * & deadline, string description, int taskNo) {

	makeConvertibleToString(deadline) ;
	cout << taskNo << "\t" << description << "\t" ;
	cout << asctime(deadline) ;
    changeBackTimePointer(deadline) ;
}

void UI::displayHomeScreen(vector<Task*> tasksToDisplay) {

 system("cls") ;
 cout << MESSAGE_WELCOME ;
 int taskNo = 0 ;
 
 vector<Task*>::iterator it = tasksToDisplay.begin() ;

 currentCursor.X = TABLE_START_POSITION_X ;
 currentCursor.Y = TABLE_START_POSITION_Y ;

 placeCursorAt(currentCursor.X, currentCursor.Y) ;

 cout << UI::TABLE_FIELDS ; 

  for( ; it != tasksToDisplay.end() ; it++) {
	 taskNo++ ;
	 currentCursor.Y++ ;
	 placeCursorAt(currentCursor.X, currentCursor.Y) ;
	 tm * startTime = (*it)->getStart() ;
	 tm * endTime = (*it)->getEnd() ;
	 string description = (*it)->getDesc() ;

	 if(startTime != NULL && endTime != NULL) {
		 displayTimedTasks(startTime, endTime, description, taskNo) ;
	 }

	 else if(startTime == NULL && endTime != NULL) {
		displayDeadlineTasks(endTime, description, taskNo) ;
	 }

	 else if(startTime != NULL && endTime == NULL) {
		displayDeadlineTasks(startTime, description, taskNo) ;
	 }

	 //floating tasks, sorted to the bottom of tasksToDisplay
	 else if(startTime == NULL && endTime == NULL) {
		 cout << taskNo << "\t" << description ;
		
	 }	
  }

}

void UI::feedback(bool result, string command) {

 currentCursor.Y += 2 ;
 placeCursorAt(currentCursor.X, currentCursor.Y) ;

 if(result == true) {
	displayTrueFeedback(command) ;
 }
 else {
	displayFalseFeedback(command) ;
 }
}

void UI::displayTrueFeedback(string command) {

	if(command == "add") {
		cout << MESSAGE_ADDED ;
	}

	else if(command == "delete") {
		cout << MESSAGE_DELETED ;
	}

	else if(command == "edit") {
		cout << MESSAGE_EDITED ;
	}
    else if(command == "search") {
		cout << MESSAGE_SEARCH_SUCCESS ;
    }
	else if(command == "exit") {

		cout << MESSAGE_EXIT ; 
		currentCursor.Y++ ;
		placeCursorAt(currentCursor.X, currentCursor.Y) ;
		system("pause") ;
	}
	else if(command == "alternate") {
		cout << MESSAGE_ALTERNATE_SUCCESS ;
	}
	else {
		cout << MESSAGE_UNDONE ;
	}
 }

void UI::displayFalseFeedback(string command) {
	
    if(command == "add") {
		cout << MESSAGE_INVALID_ADD ;
	}

	else if(command == "delete") {
		cout << MESSAGE_INVALID_DELETE ;
	}

	else if(command == "search") {
		cout << MESSAGE_INVALID_SEARCH ;
    }

	else if(command == "edit") {
		cout << MESSAGE_INVALID_EDIT ;
	}

	else if(command == "alternate") {
		cout << MESSAGE_ALTERNATE_FAIL ;
	}

	else if(command == "undo") {
		cout << MESSAGE_UNDO_FAIL ;

	}

	else if(command == "exit") {
		cout << MESSAGE_EXIT ;
		currentCursor.Y++ ;
		placeCursorAt(currentCursor.X, currentCursor.Y) ;
		system("pause") ;
	}
	else {
		cout << MESSAGE_INVALID ;
	}

 }

void UI::placeCursorAt(int x, int y) {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPosition;
    cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(hConsole, cursorPosition);
	
}

string UI::getUserInput() {

	currentCursor.Y++ ;
    placeCursorAt(currentCursor.X, currentCursor.Y) ;
    cout << MESSAGE_HELP ;
	
	currentCursor.Y += 2 ;
	placeCursorAt(currentCursor.X, currentCursor.Y) ;
	cout << MESSAGE_NEXT_COMMAND ;

	getline(cin, userInput) ;
	return userInput ;

}

void UI::printThis(string messageToUser) {

	currentCursor.Y++ ;
    placeCursorAt(currentCursor.X, currentCursor.Y) ;
	cout << messageToUser ;
}
