#include "CommandProcessor.h"
#include "stdafx.h"

vector <int> CommandProcessor::intProcessor (string userInput)
{
	vector <int> integers; 
	//asertion
	assert(integers.size() == 0) ;
	int temp = 0;
	for(int i=0;i<userInput.size();i++)
	{
		if(userInput[i] == ' '){
		integers.push_back(temp);
		temp = 0;
		}
		else{
			temp = temp*10 + (userInput[i] - 48);
		}
	}
	if(temp != 0)
		integers.push_back(temp);
	return integers;
}

string CommandProcessor::cmdProcessor (string userInput, Task*& newTask)
{
	int i, j;
	tm* sTime = NULL;
	tm* eTime = NULL;
	char description[MAX_DESC_SIZE], dateTime[MAX_TIME_SIZE], cmd[MAX_COMMAND_SIZE], singleWord[MAX_WORD_SIZE], tempSingleWord[MAX_WORD_SIZE], modInput[MAX_INPUT_SIZE];
	bool start = false, end = false, checkTime = false;
	strcpy(description, "");
	strcpy(dateTime, "");
	strcpy(cmd, "");
	strcpy(modInput,userInput.c_str());
	CommandProcessor::deleteConsecSpaces(modInput);
	userInput = modInput;
	for(i=0; i<userInput.size()&&userInput[i]!=' ';i++)
	{
		cmd[i]=userInput[i];
	}

	cmd[i]='\0';
	
	bool validCmd = CommandProcessor::actualKeyWord(cmd);
	if(validCmd == false){
			strcpy (description ,cmd);
			strcat(description, " ");
			strcpy(cmd, "add");
			
		}
	if(i==userInput.size()){
		Task *ft = new FloatingTask();
			ft->setDesc(description);
			newTask=ft;
	}
	
	else{
		i++;
		while(i < userInput.size()){

			for(j = 0; i < userInput.size() && userInput[i] != ' ' ;i++, j++){
				singleWord[j] = userInput[i];
			}
			singleWord[j] = '\0';
			
			
			checkTime = isDateTime(singleWord);
			/*strcpy(tempSingleWord, singleWord);
			if(tempSingleWord[0] == '['){
				CommandProcessor::trim(tempSingleWord);
			}*/
			if(isStart(tempSingleWord) == true || isEnd(tempSingleWord) == true)
				CommandProcessor::trim(singleWord);
			
			if(checkTime == true && (start == true || end == true)){
				strcat(singleWord, " ");
				strcat(dateTime, singleWord);
				if( i == userInput.size() ){
					CommandProcessor::parseDateTime(dateTime);
						if(start == true){
							sTime = CommandProcessor::stringToTime(dateTime);
							start = false;
						}
						else if(end == true){
							eTime = CommandProcessor::stringToTime(dateTime);
							end = false;
						}
						strcpy(dateTime, "");

				}
			}
			else {
				if(isStart(singleWord)){
					start = true;
				}

				else if(isEnd(singleWord)){
					end = true;
				}
			
				else{
					strcat(singleWord, " ");
					strcat(description, singleWord);
				}

				if(strlen(dateTime) > 0){
					CommandProcessor::parseDateTime(dateTime);
						if(start == true){
							sTime = CommandProcessor::stringToTime(dateTime);
							start = false;
						}
						else if(end == true){
							eTime = CommandProcessor::stringToTime(dateTime);
							end = false;
						}
						strcpy(dateTime, "");
				}
				
		}	
		i++;

	}

	if(eTime == NULL && sTime == NULL){
		newTask = new FloatingTask(description);
		
	}
	else if(sTime == NULL){
		newTask = new DeadlinedTask(description, eTime);
		
	}
	else if(eTime == NULL){
		newTask = new DeadlinedTask(description, sTime);
		
	}
	else{
		newTask = new TimedTask(description, sTime, eTime);
	}
	return cmd;
	}
}



void CommandProcessor::descProcessor (string userInput, Task*& newTask)
{
	int i = 0, j;
	tm* sTime = NULL;
	tm* eTime = NULL;
	char description[MAX_DESC_SIZE], dateTime[MAX_TIME_SIZE], cmd[MAX_COMMAND_SIZE], singleWord[MAX_WORD_SIZE], modInput[MAX_INPUT_SIZE];
	bool start = false, end = false, checkTime;
	strcpy(description, "");
	strcpy(dateTime, "");
	strcpy(cmd, "");
	strcpy(modInput,userInput.c_str());
	CommandProcessor::deleteConsecSpaces(modInput);
	userInput = modInput;

			while(i < userInput.size()){

			for(j = 0; i < userInput.size() && userInput[i] != ' ' ;i++, j++){
				singleWord[j] = userInput[i];
			}
			singleWord[j] = '\0';
			
			
			checkTime = isDateTime(singleWord);
			/*if(singleWord[0] == '[')
				CommandProcessor::trim(singleWord);*/
			
			if(checkTime == true && (start == true || end == true)){
				strcat(singleWord, " ");
				strcat(dateTime, singleWord);
				if( i == userInput.size() ){
					CommandProcessor::parseDateTime(dateTime);
						if(start == true){
							sTime = CommandProcessor::stringToTime(dateTime);
							start = false;
						}
						else if(end == true){
							eTime = CommandProcessor::stringToTime(dateTime);
							end = false;
						}
						strcpy(dateTime, "");

				}
			}
			else {
				if(isStart(singleWord)){
					start = true;
				}

				else if(isEnd(singleWord)){
					end = true;
				}
			
				else{
					strcat(singleWord, " ");
					strcat(description, singleWord);
				}

				if(strlen(dateTime) > 0){
					CommandProcessor::parseDateTime(dateTime);
						if(start == true){
							sTime = CommandProcessor::stringToTime(dateTime);
							start = false;
						}
						else if(end == true){
							eTime = CommandProcessor::stringToTime(dateTime);
							end = false;
						}
						strcpy(dateTime, "");
				}
				
		}	
		i++;

	}
	
	
	
	if(eTime == NULL && sTime == NULL){
		
		if(description[0] == '\0')
			strcpy(description, newTask->getDesc().c_str());  
		sTime = newTask->getStart();
		eTime = newTask->getEnd();
		if(eTime == NULL){
			newTask = new FloatingTask(description);
		}
		else if(sTime == NULL){
			newTask = new DeadlinedTask(description, eTime);
		}
		else{
			newTask = new TimedTask(description, sTime, eTime);
		}

	}
	else if(sTime == NULL){
		if(description[0] == '\0')
			strcpy(description, newTask->getDesc().c_str());
		sTime = newTask->getStart();
		
		if(sTime == NULL){
			newTask = new DeadlinedTask(description, eTime);
		}
		else{
			newTask = new TimedTask(description, sTime, eTime);
		}
	}
	else if(eTime == NULL){
		if(description[0] == '\0')
			strcpy(description, newTask->getDesc().c_str());
		eTime = newTask->getEnd();
		
		newTask = new TimedTask(description, sTime, eTime);
		
	}
	else{
		if(description[0] == '\0')
			strcpy(description, newTask->getDesc().c_str());
		newTask = new TimedTask(description, sTime, eTime);
		
	}
		
}

tm* CommandProcessor::stringToTime (string startTime)
{
	time_t curr;
	time(&curr);
	tm* now = localtime(&curr);
	now->tm_mon += 1;
	now->tm_year +=  1900;
	tm* sTime=new tm;
	int index=0;
	
	int date=(startTime[0]-ASCII_VALUE_0)*10+(startTime[1]-ASCII_VALUE_0);
	int month=(startTime[2]-ASCII_VALUE_0)*10+(startTime[3]-ASCII_VALUE_0);
	int year=(startTime[4]-ASCII_VALUE_0)*1000+(startTime[5]-ASCII_VALUE_0)*100+(startTime[6]-ASCII_VALUE_0)*10+(startTime[7]-ASCII_VALUE_0);
	if(date != 0){
		sTime->tm_mday=date;
	}
	else{
		sTime->tm_mday = now->tm_mday;
	}
	if(month != 0){
		sTime->tm_mon=month;
	}
	else{
		sTime->tm_mon = now->tm_mon;
	}
	if(year !=0){
		sTime->tm_year=year;
	}
	else{
		sTime->tm_year = now->tm_year ;
	}
	int hour, min;
	if(strlen(startTime.c_str()) > 8){
		hour=(startTime[8]-ASCII_VALUE_0)*10+(startTime[9]-ASCII_VALUE_0);
		min=(startTime[10]-ASCII_VALUE_0)*10+(startTime[11]-ASCII_VALUE_0);
	}
	else{
		hour = now->tm_hour;
		min = now->tm_min;
	}
	sTime->tm_hour=hour;
	sTime->tm_min=min;
	/*if(sTime->tm_year <= now->tm_year){
		if((sTime ->tm_mday < now ->tm_mday) && (sTime->tm_mon < now->tm_mon)){
			sTime->tm_mon++;
		}
		if((sTime ->tm_mon < now ->tm_mon)){
			sTime->tm_year++;
		}
	}*/
	return sTime;
}
bool CommandProcessor::actualKeyWord(char userCmd[MAX_COMMAND_SIZE]){

	bool isAdd, isRemove, isEdit, isSearch, isExit, isUndo,isRedo;
	
	isAdd = CommandProcessor::isFound(userCmd, addList);
	isRemove = CommandProcessor::isFound(userCmd, removeList);
	isEdit = CommandProcessor::isFound(userCmd, editList);
	isSearch = CommandProcessor::isFound(userCmd, searchList);
	isExit = CommandProcessor::isFound(userCmd, exitList);
	isUndo = CommandProcessor::isFound(userCmd, undoList);
	isRedo=CommandProcessor::isFound(userCmd,redoList);

	if(isAdd)
		strcpy(userCmd, "add");
	else if(isRemove)
		strcpy(userCmd, "delete");
	else if(isEdit)
		strcpy(userCmd, "edit");
	else if(isSearch)
		strcpy(userCmd, "search");
	else if(isExit)
		strcpy(userCmd, "exit");
	else if(isUndo)
		strcpy(userCmd, "undo");
	else if(isRedo)
		strcpy(userCmd, "redo");
	
	if(isAdd == false && isRemove == false && isEdit == false && isSearch == false && isExit == false && isUndo == false && isRedo==false)
		return false;
	else 
		return true;

}

bool CommandProcessor::isFound(char cmd[MAX_COMMAND_SIZE], const char cmdList[][MAX_COMMAND_SIZE]){

	int i = 0;
	while(strcmpi("-1", cmdList[i]) != 0){
		if(strcmpi(cmd, cmdList[i]) == 0)
			return true;
		i++;
	}

	return false;
}


bool CommandProcessor::isStart(char singleWord[MAX_WORD_SIZE]){
	
    return CommandProcessor::isFound(singleWord, startList);

}

bool CommandProcessor::isEnd(char singleWord[MAX_WORD_SIZE]){
	
	return CommandProcessor::isFound(singleWord, endList);

}

void CommandProcessor::trim(char word[MAX_COMMAND_SIZE]){
	char trimmed[MAX_COMMAND_SIZE];
	int i;
	for( i = 0;  word[i + 1] != ']'; i++){
		trimmed[i] = word[i + 1];
	}
	trimmed[i] = '\0';
	strcpy(word, trimmed);
}

bool CommandProcessor::isDateTime(char singleWord[MAX_WORD_SIZE]){
	bool time = isFound(singleWord, timeList);
	if(time == true){
		return time;
	}
	else{
		time = isNumericalTime(singleWord);
	}
	return time;
}

bool CommandProcessor::isNumericalTime(char singleWord[MAX_COMMAND_SIZE]){
	int first = -1, second = -1, third = -1;
	bool returnVal = false;
	CommandProcessor::splitTime(singleWord, first, second, third);

	returnVal = CommandProcessor::isDate(first, second, third);
	
	if(returnVal == false){
	returnVal = CommandProcessor::isTime(first, second, third);
	}
	
	return returnVal;
}
	
bool CommandProcessor::isDay(int input){
	if(input >=1 && input <= 31){
		return true;
	}
	else return false;
}

bool CommandProcessor::isMonth(int input){
	if(input >=1 && input <= 12)
		return true;
	else 
		return false;
}

bool CommandProcessor::isYear(int input){
	if(input > 0 && input < 100){
		return true;
	}
	else if(input > 1000){
		return true;
	}
	else
		return false;
}

bool CommandProcessor::isHour(int input){
	if(input >= 0 && input <= 24)
		return true;
	else 
		return false;
}

bool CommandProcessor::isMinute(int input){
	if(input >= 0 && input <= 60)
		return true;
	else 
		return false;
}

bool CommandProcessor::parseDateTime(char dateTime[MAX_TIME_SIZE]){
	char singleWord[MAX_TIME_SIZE], finalTime[MAX_TIME_SIZE], temp[MAX_WORD_SIZE];
	bool time = false, date = false;
	int next = 0;
	strcpy(finalTime, "");
	int i = 0, j, tempTime = 0, first = -1, second = -1, third = -1;

	while(i < strlen(dateTime)){
		first = second = third = -1;
		for(j = 0; i < strlen(dateTime) && dateTime[i] != ' '; i++, j++){
			singleWord[j] = dateTime[i];
		}
		singleWord[j] = '\0';
		i++;
		bool isNumeric = CommandProcessor::isNumericalTime(singleWord);
		if(isNumeric == true){
			CommandProcessor::splitTime(singleWord, first, second, third);
			time = isTime(first, second, third);
			date = isDate(first, second, third);
			char *posth = strstr(dateTime, "th"), *posst = strstr(dateTime, "st"), *posnd = strstr(dateTime, "nd");
			if(posth != NULL){
				date = true;
				time = false;
				char *tmp = posth + 2;
				*(posth - 1) = '\0';
				strcat(dateTime, tmp);
			}
			else if(posnd != NULL){
				date = true;
				time = false;
				char *tmp = posnd + 2;
				*(posnd - 1) = '\0';
				strcat(dateTime, tmp);
			}
			else if(posst != NULL){
				date = true;
				time = false;
				char *tmp = posst + 2;
				*(posst - 1) = '\0';
				strcat(dateTime, tmp);
			}

			
			if(time == true && date == true){
				if(i >= (strlen(dateTime) - 3)){
					CommandProcessor::addZeroes(singleWord);
					CommandProcessor::convertTime(singleWord);
					if(strlen(finalTime) == 0){
						strcat(finalTime, "00000000");
					}
					finalTime[8] = '\0';
					strcat(finalTime, singleWord);
				}
			
				else{
					CommandProcessor::addZeroes(singleWord);
					CommandProcessor::convertDate(singleWord);
					strcat(finalTime, singleWord);
				}
			}
			
			else if(time == true){
				CommandProcessor::addZeroes(singleWord);
				CommandProcessor::convertTime(singleWord);
				if(strlen(finalTime) == 0){
						strcat(finalTime, "00000000");
					}
				finalTime[8] = '\0';
				strcat(finalTime, singleWord);
			}
			else if(date == true){
				CommandProcessor::addZeroes(singleWord);
				CommandProcessor::convertDate(singleWord);
				strcat(finalTime, singleWord);
			}
		}
		else if(strcmpi(singleWord, "pm") != 0){
			CommandProcessor::parseCharTime(singleWord, finalTime);
		}
		else{	
			if(strlen(finalTime) != 0){
					int hours = (finalTime[8] - 48)*10 + (finalTime[9] - 48);
					int min = (finalTime[10] - 48)*10 + (finalTime[11] - 48);
					if(hours <= 12){
						finalTime[8] = '\0';
						hours += 12;
						itoa(hours, temp, 10);
						strcat(finalTime, temp);
						if(min <10){
							strcat(finalTime, "0");
						}
						itoa(min, temp, 10);
						strcat(finalTime, temp);
					}
			
			
			}
		}
	}
		
		
	
	
	if(strlen(finalTime) == 8){
		strcat(finalTime, "0000");
	}
	strcpy(dateTime, finalTime);
	
	return true;
}


void CommandProcessor::convertDate(char Date[MAX_TIME_SIZE]){
	
	int j = 0, k = 0,  year, month;
	char tempTime[MAX_TIME_SIZE], temp[MAX_TIME_SIZE];
	strcpy(tempTime, "");
	strcpy(temp, "");
	strcpy(tempTime, Date);
	time_t t;
	time(&t);
	tm* curr = localtime(&t);
	curr->tm_mon += 1;
	curr->tm_year += 1900;
	//when date is dd/mm/yy
	if(strlen(tempTime) == 6){
		year = (tempTime[4] - 48)*10 + (tempTime[5] - 48);
		if(year >= 90){
			year = 1900 + year;
		}
		else{
			year = 2000 + year;
		}
		tempTime[4] = '\0';
		itoa(year, temp, 10);
		strcat(tempTime, temp);
	}
	//dd/mm
	else if(strlen(tempTime) == 4){
		year = curr->tm_year;
		itoa(year, temp, 10);
		strcat(tempTime, temp);
	}
	//dd
	else if(strlen(tempTime) == 2)
	{
		month = curr->tm_mon;
		itoa(month, temp, 10);
		strcat(tempTime, temp);
		year = curr->tm_year ;
		itoa(year, temp, 10);
		strcat(tempTime, temp);
	}
	strcpy(Date, tempTime);
}
void CommandProcessor::convertTime(char Date[MAX_TIME_SIZE]){
	int j = 0, k = 0,  year;
	char tempTime[MAX_TIME_SIZE];
	
	for(j = 0; j < strlen(Date); j++){
		if(isalnum(Date[j]) && !(isalpha(Date[j]))){
		tempTime[j] = Date[j];
		}
	}
	tempTime[j] = '\0';
	if(strlen(tempTime) == 2){
		strcat(tempTime, "00");
	}
	strcpy(Date, tempTime);
}

void CommandProcessor::addZeroes(char input[MAX_TIME_SIZE]){
	char newDate[MAX_TIME_SIZE], tempDate[MAX_TIME_SIZE];
	strcpy(newDate, "");
	int i = 0, j = 0;
	int buffer;
	while(i < strlen(input)){
		buffer = 0;
		for(; ( isalnum(input[i]) && !isalpha(input[i]) ) &&(i < strlen(input)); i++){
			buffer = buffer * 10 + (input[i] - 48) ;
		}
		i++;
			if(buffer < 10){
				newDate[j] = '0';
				j++;
				newDate[j] = buffer + 48;
				j++;
				newDate[j] = '\0';
			}
			else{
				itoa(buffer, tempDate, 10);
				strcat(newDate, tempDate);
				j += 2;
			}
	}
	strcpy(input, newDate);
}

bool CommandProcessor::isDate(int first, int second, int third ){
	bool returnVal = false;
	if(third == -1 && second == -1){
			if(isDay(first) == true || isYear(first) ==  true){
				returnVal = true;
			}
			else{
				returnVal = false;
			}
		}
	else if(third == -1){
		if(isDay(first) == true && isMonth(second)){
				returnVal = true;
			}
			else{
				returnVal = false;
			}
	}
		else{
			
			if(isDay(first) == true && isMonth(second) == true && isYear(third) == true){
				returnVal = true;
			}
			else{
				returnVal = false;
			}
		}
		return returnVal;
}

bool CommandProcessor::isTime(int first, int second, int third ){
	bool returnVal = false;
	if(third == -1){
		if(second == -1){
			if(isHour(first) == true){
				returnVal = true;
			}
		}
		else{
			if(isHour(first) == true && isMinute(second) == true){
				returnVal = true;
			}
		}
	}
		else{
			returnVal = false;
		}

	return returnVal;
}
void CommandProcessor::splitTime(char singleWord[MAX_COMMAND_SIZE], int &first, int &second, int&third){
	int buffer, i;
	buffer = 0;
	i = 0;
	while(isalnum(singleWord[i]) && !isalpha(singleWord[i])  && i < strlen(singleWord)){
		buffer = buffer * 10 + (singleWord[i] - 48);
		i++;
	}
	
	if(i <= strlen(singleWord)){
	first = buffer;
	}
	
	i++;
	if(i < strlen(singleWord)){
		buffer = 0;
		while(isalnum(singleWord[i]) && !isalpha(singleWord[i])  && i < strlen(singleWord)){
			buffer = buffer * 10 + (singleWord[i] - 48);
			i++;
		}
	}
	if(i <= strlen(singleWord)){
	second = buffer;
	}
	
	i++;
	if(i < strlen(singleWord)){
		buffer = 0;
		while(isalnum(singleWord[i]) && !isalpha(singleWord[i])  && i < strlen(singleWord)){
			buffer = buffer * 10 + (singleWord[i] - 48);
			i++;
		}
	}

	if(i <= strlen(singleWord)){
	third = buffer;
	}
}

void CommandProcessor::parseCharTime(char singleWord[MAX_WORD_SIZE], char finalTime[MAX_TIME_SIZE]){
	time_t curr;
	time(&curr);
	tm *now = localtime(&curr);
	now->tm_mon++;
	now->tm_year += 1900;
	tm dateTime = *now;
	static int no_next = 0, day = 0, after = 0, tomorrow = 0;
	int wday = now->tm_wday;
	if(strlen(finalTime) != 0){
		dateTime = *CommandProcessor::stringToTime(finalTime);
		dateTime.tm_wday = wday;
	}
	bool isDay, isMonth;
	char tmp[MAX_TIME_SIZE];
	if(strlen(finalTime) == 0){
				
		CommandProcessor::dateToString(now, finalTime);
		
	}
		isMonth = isFound(singleWord, monthList);
		isDay = isFound(singleWord, days);
		if(isDay ==  true){
			CommandProcessor::incrementDate(&dateTime, (no_next - 1)*7);
			strcpy(finalTime, "");
			CommandProcessor::dateToString(&dateTime, finalTime);
			dateTime = evaluateDate(singleWord, finalTime);
			no_next = 0;
		}
		else if(isMonth == true){
			if(no_next != 0){
			CommandProcessor::incrementYear(&dateTime, (no_next - 1));
			}
			
			strcpy(finalTime, "");
			CommandProcessor::dateToString(&dateTime, finalTime);
			dateTime = evaluateMonth(singleWord, finalTime);
			no_next = 0;
		}
		else if(strcmpi(singleWord, "day") == 0){
			day = 1;
		}
		else if(strcmpi(singleWord, "after") == 0){
			after = 1;
		}
		else if(strcmpi(singleWord, "tomorrow") == 0){
			tomorrow = 1;
		}
		else if(strcmpi(singleWord, "now") == 0){
			dateTime = *now;
			CommandProcessor::dateToString(&dateTime, finalTime);
		}
		else if(strcmpi(singleWord, "week") == 0){
			CommandProcessor::incrementDate(&dateTime, no_next*7);
			strcpy(finalTime, "");
			CommandProcessor::dateToString(&dateTime, finalTime);
			no_next = 0;
		}
		else if(strcmpi(singleWord, "month") == 0){
			CommandProcessor::incrementMonth(&dateTime, no_next);
			strcpy(finalTime, "");
			CommandProcessor::dateToString(&dateTime, finalTime);
			no_next = 0;
		}
		else if(strcmpi(singleWord, "year") == 0){
			CommandProcessor::incrementYear(&dateTime, no_next);
			strcpy(finalTime, "");
			CommandProcessor::dateToString(&dateTime, finalTime);
			no_next = 0;
		}
		else{
			if(strcmpi(singleWord, "next") == 0){
				no_next++;
			}
		}
		if(day == 1 && after == 1 && tomorrow == 1){
			dateTime = *now;
			if(no_next != 0){
				CommandProcessor::incrementDate(&dateTime, 2 + (no_next - 1));
				no_next = 0;
			}
			else{
			CommandProcessor::incrementDate(&dateTime, 2);
			}
			CommandProcessor::dateToString(&dateTime, finalTime);
			day = after = tomorrow = 0;

		}
		else if(tomorrow == 1){
			dateTime = *now;
			if(no_next != 0){
				CommandProcessor::incrementDate(&dateTime, 1 + (no_next - 1));
				no_next = 0;
			}
			else{
				CommandProcessor::incrementDate(&dateTime, 1 );
			}
			CommandProcessor::dateToString(&dateTime, finalTime);
			tomorrow = 0;
		}
		strcpy(finalTime, "");
		CommandProcessor::dateToString(&dateTime, finalTime);
}

tm CommandProcessor::evaluateDate(char day[MAX_TIME_SIZE], char finalTime[MAX_TIME_SIZE]){
	time_t curr;
	time(&curr);
	tm* returnTime ;
	returnTime = localtime(&curr); 
	returnTime->tm_mon++;
	returnTime->tm_year += 1900;
	int wday = returnTime->tm_wday;
	
	if(strlen(finalTime) != 0){
		returnTime = CommandProcessor::stringToTime(finalTime);
		returnTime->tm_wday = wday;
	}
	int days;
	bool isMonday = !(bool)(strcmpi(day, "monday") );
	bool isTuesday = !(bool)(strcmpi(day, "tuesday"));
	bool isWednesday = !(bool)(strcmpi(day, "wednesday"));
	bool isThursday = !(bool)(strcmpi(day, "thursday"));
	bool isFriday = !(bool)(strcmpi(day, "friday"));
	bool isSaturday = !(bool)(strcmpi(day, "saturday"));
	bool isSunday = !(bool)(strcmpi(day, "sunday"));
	
	if(isMonday){
		if(returnTime->tm_wday > 1){
			days = 7 - (returnTime->tm_wday - 1) ;
		}
		else{
			days = 1 - returnTime->tm_wday;
		}
	}
	if(isTuesday){
		if(returnTime->tm_wday > 2){
			days = 7 - (returnTime->tm_wday - 2) ;
		}
		else{
			days = 2 - returnTime->tm_wday;
		}
	}
	if(isWednesday){
		if(returnTime->tm_wday > 3){
			days = 7 - ( returnTime->tm_wday - 3) ;
		}
		else{
			days = 3 - returnTime->tm_wday;
		}
	}
	if(isThursday){
		if(returnTime->tm_wday > 4){
			days = 7 - ( returnTime->tm_wday - 4) ;
		}
		else{
			days = 4 - returnTime->tm_wday;
		}
	}
	if(isFriday){
		if(returnTime->tm_wday > 5){
			days = 7 - ( returnTime->tm_wday - 5) ;
		}
		else{
			days = 5 - returnTime->tm_wday;
		}
	}
	if(isSaturday){
		if(returnTime->tm_wday > 6){
			days = 7 - ( returnTime->tm_wday - 6) ;
		}
		else{
			days = 6 - returnTime->tm_wday;
		}
	}
	if(isSunday){
		if(returnTime->tm_wday > 0){
			days = 7 - ( returnTime->tm_wday - 0) ;
		}
		else{
			days = 0;
		}
	}
	CommandProcessor::incrementDate(returnTime, days);

	return *returnTime;
}

void CommandProcessor::incrementDate(tm *date, int days){

	bool isLeap;
	switch(date->tm_mon){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: 
		date->tm_mon += (date->tm_mday + days) / 32;
		date->tm_mday = (date->tm_mday + days) % 31;
		
		break;
	case 2:
		isLeap = CommandProcessor::isLeapYear(date->tm_yday);
		if(isLeap == true){
			date->tm_mon += (date->tm_mday + days) / 30;
			date->tm_mday = (date->tm_mday + days) % 29;
		}
		else{
			date->tm_mon += (date->tm_mday + days) / 29;
			date->tm_mday = (date->tm_mday + days) % 28;
		}
		break;
	default:
		date->tm_mon += (date->tm_mday + days) / 31;
		date->tm_mday = (date->tm_mday + days) % 30;
		break;
	}
	date->tm_year += date->tm_mon / 13;
	
}


void CommandProcessor::incrementMonth(tm *date, int months){
	date->tm_year += months / 13;
	date->tm_mon += months % 12;
}
void CommandProcessor::incrementYear(tm *date, int years){
	date->tm_year += years;
}

bool CommandProcessor::isLeapYear(int year){
	if(((year % 100) == 0) && ((year % 400) == 0)){
		return true;
	}
	else if((year % 100) == 0){
		return false;
	}
	else if((year % 4) == 0){
		return true;
	}
	else {
		return false;
	}
}

void CommandProcessor::dateToString(tm* date, char finalDate[MAX_TIME_SIZE]){

	char tmp[MAX_TIME_SIZE];
	if(date->tm_mday < 10){
			strcat(finalDate, "0");
		}
		itoa(date->tm_mday,tmp , 10);
		strcat(finalDate, tmp);

		if(date->tm_mon < 10){
			strcat(finalDate, "0");
		}
		itoa(date->tm_mon ,tmp , 10);
		strcat(finalDate, tmp);

		if(date->tm_year < 10){
			strcat(finalDate, "0");
		}
		itoa(date->tm_year ,tmp , 10);
		strcat(finalDate, tmp);

		if(date->tm_hour < 10){
			strcat(finalDate, "0");
		}
		itoa(date->tm_hour,tmp , 10);
		strcat(finalDate, tmp);

		if(date->tm_min < 10){
			strcat(finalDate, "0");
		}
		itoa(date->tm_min,tmp , 10);
		strcat(finalDate, tmp);
}

void CommandProcessor::deleteConsecSpaces(char input[MAX_INPUT_SIZE]){
	int i, j;
	for(i = 0; i < strlen(input); i++){
		if(input[i] == ' ' && input[i + 1] == ' '){
			for(j = i; j < strlen(input); j++){
				input[j] = input[j + 1];
			}
			i--;
		}
	}
}

tm CommandProcessor::evaluateMonth(char month[MAX_TIME_SIZE], char finalTime[MAX_TIME_SIZE]){
	time_t curr;
	time(&curr);
	tm* returnTime ,*now;
	now = localtime(&curr);
	now->tm_mon++;
	now->tm_mday = 1;
	now->tm_year += 1900;
	int wday = now->tm_wday;
	
	if(strlen(finalTime) != 0){
		returnTime = CommandProcessor::stringToTime(finalTime);
		returnTime->tm_wday = wday;
	}
	else{
		returnTime = now;
	}
	
	
	bool isJan = !(bool)(strcmpi(month, "January") );
	bool isFeb = !(bool)(strcmpi(month, "February"));
	bool isMar = !(bool)(strcmpi(month, "March"));
	bool isApr = !(bool)(strcmpi(month, "April"));
	bool isMay = !(bool)(strcmpi(month, "May"));
	bool isJun = !(bool)(strcmpi(month, "June"));
	bool isJul = !(bool)(strcmpi(month, "July"));
	bool isAug = !(bool)(strcmpi(month, "August"));
	bool isSep = !(bool)(strcmpi(month, "September"));
	bool isOct = !(bool)(strcmpi(month, "October"));
	bool isNov = !(bool)(strcmpi(month, "November"));
	bool isDec = !(bool)(strcmpi(month, "December"));

	if(isJan == true){
		returnTime->tm_year++;
		returnTime->tm_mon = 1;
	}
	else if(isFeb == true){
		returnTime->tm_mon = 2;
		if(now->tm_mon > 1){
			returnTime->tm_year++;			
		}
	}
	else if(isMar == true){
		returnTime->tm_mon = 3;
		if((now->tm_mon > 3) || (now ->tm_mon == 3 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
		
	}
	else if(isApr == true){
		returnTime->tm_mon = 4;
		if((now->tm_mon > 4) || (now ->tm_mon == 4 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isMay == true){
		returnTime->tm_mon = 5;
		if((now->tm_mon > 5) || (now ->tm_mon == 5 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isJun == true){
		returnTime->tm_mon = 6;
		if((now->tm_mon > 6) || (now ->tm_mon == 6 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isJul == true){
		returnTime->tm_mon = 7;
		if((now->tm_mon > 7) || (now ->tm_mon == 7 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isAug == true){
		returnTime->tm_mon = 8;
		if((now->tm_mon > 8) || (now ->tm_mon == 8 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isSep == true){
		returnTime->tm_mon = 9;
		if((now->tm_mon > 9) || (now ->tm_mon == 9 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isOct == true){
		returnTime->tm_mon = 10;
		if((now->tm_mon > 10) || (now ->tm_mon == 10 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isNov == true){
		returnTime->tm_mon = 11;
		if((now->tm_mon > 11) || (now ->tm_mon == 11 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	else if(isDec == true){
		returnTime->tm_mon = 12;
		if((now->tm_mon > 12) || (now ->tm_mon == 12 && now->tm_mday > returnTime->tm_mday)){
			returnTime->tm_year++;			
		}
	}
	return *returnTime;
}