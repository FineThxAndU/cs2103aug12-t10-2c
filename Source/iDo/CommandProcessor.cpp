#include "CommandProcessor.h"
#include "DeadlinedTask.h"
#include "FloatingTask.h"
#include "TimedTask.h"


vector <int> CommandProcessor::intProcessor (string userInput)
{
	vector <int> integers; 
	for(int i=0;i<userInput.size();i++)
	{
		integers.push_back(userInput[i] - 48);
	}
	return integers;
}

string CommandProcessor::cmdProcessor (string userInput, Command*& newCommand)
{
	int i, j;
	tm* sTime = NULL;
	tm* eTime = NULL;
	char description[MAX_DESC_SIZE], startTime[MAX_TIME_SIZE], endTime[MAX_TIME_SIZE], cmd[MAX_COMMAND_SIZE], singleWord[MAX_COMMAND_SIZE];
	bool start = false, end = false;
	int state = 3;
	strcpy(description, "");
	strcpy(startTime, "");
	strcpy(endTime, "");
	strcpy(cmd, "");

	for(i=0; i < userInput.size() && userInput[i]!=' ';i++)
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
			strcat(singleWord, " ");
			i++;

			if(start == true && state == 1){
				sTime = CommandProcessor::stringToTime(singleWord);
				state = 2;
			}
			else if(end == true && state == 1){
				eTime = CommandProcessor::stringToTime(singleWord);
				state = 2;
			}
			if(singleWord[0] == '[')
				CommandProcessor::trim(singleWord);
			start = isStart(singleWord);
			end = isEnd(singleWord);
			
			if(start != false || end != false){
				state = 1;
			}

			if(state == 2){
				state++;
			}
			else if(state == 3){
				strcat(description, singleWord);
			}
			
		}
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

void CommandProcessor::descProcessor (string userInput, Task*& newTask)
{
	int i = 0, j;
	tm* sTime = NULL;
	tm* eTime = NULL;
	char description[MAX_DESC_SIZE], startTime[MAX_TIME_SIZE], endTime[MAX_TIME_SIZE], cmd[MAX_COMMAND_SIZE], singleWord[MAX_COMMAND_SIZE];
	bool start = false, end = false;
	int state = 3;
	strcpy(description, "");
	strcpy(startTime, "");
	strcpy(endTime, "");
	strcpy(cmd, "");

	while(i < userInput.size()){

			for(j = 0; i < userInput.size() &&  userInput[i] != ' ' ;i++, j++){
				singleWord[j] = userInput[i];
			}
			singleWord[j] = '\0';
			strcat(singleWord, " ");
			i++;

			if(start == true && state == 1){
				sTime = CommandProcessor::stringToTime(singleWord);
				state = 2;
			}
			else if(end == true && state == 1){
				eTime = CommandProcessor::stringToTime(singleWord);
				state = 2;
			}
			if(singleWord[0] == '[')
				CommandProcessor::trim(singleWord);
			start = isStart(singleWord);
			end = isEnd(singleWord);
			
			if(start != false || end != false){
				state = 1;
			}

			if(state == 2){
				state++;
			}
			else if(state == 3){
				strcat(description, singleWord);
			}
			
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
	tm* sTime=new tm;
	int index=0;
	int date=(startTime[0]-ASCII_VALUE_0)*10+(startTime[1]-ASCII_VALUE_0);
	int month=(startTime[2]-ASCII_VALUE_0)*10+(startTime[3]-ASCII_VALUE_0);
	int year=(startTime[4]-ASCII_VALUE_0)*1000+(startTime[5]-ASCII_VALUE_0)*100+(startTime[6]-ASCII_VALUE_0)*10+(startTime[7]-ASCII_VALUE_0);
	sTime->tm_mday=date;
	sTime->tm_mon=month;
	sTime->tm_year=year;
	int hour=(startTime[8]-ASCII_VALUE_0)*10+(startTime[9]-ASCII_VALUE_0);
	int min=(startTime[10]-ASCII_VALUE_0)*10+(startTime[11]-ASCII_VALUE_0);
	sTime->tm_hour=hour;
	sTime->tm_min=min;
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


bool CommandProcessor::isStart(char singleWord[MAX_COMMAND_SIZE]){
	
    return CommandProcessor::isFound(singleWord, startList);

}

bool CommandProcessor::isEnd(char singleWord[MAX_COMMAND_SIZE]){
	
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