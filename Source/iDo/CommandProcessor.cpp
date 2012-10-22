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

string CommandProcessor::cmdProcessor (string userInput, Task*& newTask)
{

	int i, j;
	tm* sTime;
	tm* eTime;
	char description[MAX_DESC_SIZE], startTime[MAX_TIME_SIZE], endTime[MAX_TIME_SIZE], cmd[MAX_COMMAND_SIZE];
	strcpy(description, "");
	strcpy(startTime, "");
	strcpy(endTime, "");
	strcpy(cmd, "");

	for(i=0; i<userInput.size()&&userInput[i]!=' ';i++)
	{
		cmd[i]=userInput[i];
	}

	cmd[i]='\0';
	bool validCmd = CommandProcessor::actualKeyWord(cmd);
	if(validCmd == false){
			strcpy (description ,cmd);
			strcpy(description, strcat(description, " "));
			strcpy(cmd, "add");
		}
	if(i==userInput.size()){
		Task *ft = new FloatingTask;
			ft->setDesc(description);
			newTask=ft;
	}
	

	else
	{
		i++;
		for(j = strlen(description) ; i<userInput.size() && userInput[i]!=',';i++, j++)
		{
			description[j]=userInput[i];
		}
		description[j]='\0';
		

		if(i==userInput.size())
		{
			Task *ft = new FloatingTask;
			ft->setDesc(description);
			newTask=ft;

		}
		else
		{
			i++;
			for(j = 0; i<userInput.size() && userInput[i]!=',';i++,j++)
			{
				startTime[j]=userInput[i];
			}
			startTime[j]='\0';
			sTime=stringToTime(startTime);
			
			if(i==userInput.size())
			{
				eTime = sTime;
				sTime=NULL;
				strcpy(startTime,"\0");
				strcpy(endTime,"\0");

				DeadlinedTask *dt= new DeadlinedTask;
				dt->setDesc(description);
				dt->setEnd(eTime);
				dt->setStart(sTime);
				newTask=dt;
			}

			else
			{
				i++;
				for(j = 0; i<userInput.size() && userInput[i]!=',';i++, j++)
				{
					endTime[j]=userInput[i];
				
				}
				endTime[j]='\0';
				eTime=stringToTime(endTime);
				TimedTask *tt= new TimedTask;
				tt->setDesc (description);
				tt->setEnd(eTime);
				tt->setStart(sTime);
				newTask=tt;
			}
		}
	}
	return cmd;
}

void CommandProcessor::descProcessor (string userInput, Task*& newTask)
{
	int i=0,j=0;
	char description[MAX_DESC_SIZE], startTime[MAX_TIME_SIZE], endTime[MAX_TIME_SIZE];
	tm* sTime = NULL, *eTime = NULL;
	for(; i<userInput.size() && userInput[i]!=',';i++)
		{
			description[i]=userInput[i];
		}
		description[i]='\0';
		if(i==userInput.size())
		{
			FloatingTask *ft=new FloatingTask;
			ft->setDesc( description);
			ft->setEnd(NULL);
			ft->setStart(NULL);
			newTask=ft;

		}
		else
		{
			i++;
			for(j=0; i<userInput.size() && userInput[i]!=',';i++,j++)
			{
				startTime[j]=userInput[i];
			}
			startTime[j]='\0';
			sTime=stringToTime(startTime);
			if(i==userInput.size())
			{
				eTime = sTime;
				sTime = NULL;
				startTime[0]='\0';
				DeadlinedTask *dt= new DeadlinedTask;
				dt->setDesc(description);
				dt->setEnd(eTime);
				dt->setStart(sTime);
				newTask=dt;
			}
			else
			{
				i++;
				for(j=0; i<userInput.size() && userInput[i]!=',';j++,i++)
				{
					endTime[j]=userInput[i];
				
				}
				endTime[j]='\0';
				eTime=stringToTime(endTime);
				TimedTask *tt= new TimedTask;
				tt->setDesc (description);
				tt->setEnd(eTime);
				tt->setStart(sTime);
				newTask=tt;
			}
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

	bool isAdd, isRemove, isEdit, isSearch, isExit, isUndo;
	
	isAdd = CommandProcessor::isFound(userCmd, addList);
	isRemove = CommandProcessor::isFound(userCmd, removeList);
	isEdit = CommandProcessor::isFound(userCmd, editList);
	isSearch = CommandProcessor::isFound(userCmd, searchList);
	isExit = CommandProcessor::isFound(userCmd, exitList);
	isUndo = CommandProcessor::isFound(userCmd, undoList);

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
	
	if(isAdd == false && isRemove == false && isEdit == false && isSearch == false && isExit == false && isUndo == false)
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