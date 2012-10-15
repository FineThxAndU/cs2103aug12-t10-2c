#include <iostream>
#include <string>
#include <time.h>
#include "CommandProcessor.h"
#include "DeadlinedTask.h"
#include "FloatingTask.h"
#include "task.h"
#include "TimedTask.h"
static int const ASCII_VALUE_0 = 48;

vector <int> CommandProcessor::intProcessor (string userInput)
{
	vector <int> integers; 
	for(int i=0;i<userInput.size();i++)
	{
		integers.push_back(userInput[i]);
	}
	return integers;
}

string CommandProcessor::cmdProcessor (string userInput, Task* newTask)
{
	string cmd;
	int i;
	tm* sTime;
	tm* eTime;
	string description, startTime, endTime;
	
	for(i=0; i<userInput.size() && userInput[i]!=' ';i++)
	{
		cmd[i]=userInput[i];
	}
	cmd[i]='/0';
	if(i==userInput.size())
		newTask='\0';
	else
	{
		i++;
		for(; i<userInput.size() && userInput[i]!=',';i++)
		{
			description[i]=userInput[i];
		}
		description[i]='\0';
		if(i==userInput.size())
		{
			FloatingTask *ft=new FloatingTask;
			ft->setDesc( description);
			newTask=ft;

		}
		else
		{
			i++;
			for(; i<userInput.size() && userInput[i]!=',';i++)
			{
				startTime[i]=userInput[i];
			}
			startTime[i]='\0';
			sTime=stringToTime(startTime);


			
			if(i==userInput.size())
			{
				eTime = sTime;
				DeadlinedTask *dt= new DeadlinedTask;
				dt->setDesc(description);
				dt->setEnd(eTime);
				dt->setStart(NULL);
				newTask=dt;
			}
			else
			{
				i++;
				for(; i<userInput.size() && userInput[i]!=',';i++)
				{
					endTime[i]=userInput[i];
				
				}
				endTime[i]='\0';
				eTime=stringToTime(endTime);
				TimedTask *tt= new TimedTask;
				tt->setDesc (description);
				tt->setEnd(eTime);
				tt->setStart(sTime);
			}
		}
	}
	return cmd;
}

void CommandProcessor::descProcessor ( string userInput, Task* newTask)
{
	int i=0;
	string description, startTime, endTime;
	tm* sTime, *eTime;
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
			for(; i<userInput.size() && userInput[i]!=',';i++)
			{
				startTime[i]=userInput[i];
			}
			startTime[i]='\0';
			sTime=stringToTime(startTime);
			if(i==userInput.size())
			{
				eTime=sTime;
				startTime='\0';
				DeadlinedTask *dt= new DeadlinedTask;
				dt->setDesc(description);
				dt->setEnd(eTime);
				dt->setStart(sTime);
				newTask=dt;
			}
			else
			{
				i++;
				for(; i<userInput.size() && userInput[i]!=',';i++)
				{
					endTime[i]=userInput[i];
				
				}
				endTime[i]='\0';
				eTime=stringToTime(endTime);
				TimedTask *tt= new TimedTask;
				tt->setDesc (description);
				tt->setEnd(eTime);
				tt->setStart(sTime);
			}
		}
	}

tm* CommandProcessor::stringToTime (string startTime)
{
	tm* sTime=new tm;
	int index=0;
	int date=(startTime[index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	int month=(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	int year=(startTime[++index]-ASCII_VALUE_0)*1000+(startTime[++index]-ASCII_VALUE_0)*100+(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	sTime->tm_mday=date;
	sTime->tm_mon=month;
	sTime->tm_year=year;
	int hour=(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	int min=(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	sTime->tm_hour=hour;
	sTime->tm_min=min;
	return sTime;
}
