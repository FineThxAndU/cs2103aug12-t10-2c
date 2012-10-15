#include <iostream>
#include <string>
#include <time.h>
#include "CommandProcessor.h"
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
	tm sTime, eTime;
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
			floatingTask *ft=new floatingTask;
			ft->setter( description);
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
				DeadlineTask *dt= new DeadlineTask;
				dt->setter(description,eTime);
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
				timedTask tt= new timedTask;
				tt->setter (description, sTime, eTime);
			}
		}
	}
	return cmd;
}

void CommandProcessor::descProcessor ( string userInput)
{
	int i=0;
	string description, startTime, endTime;
	for(; i<userInput.size() && userInput[i]!=',';i++)
		{
			description[i]=userInput[i];
		}
		description[i]='\0';
		if(i==userInput.size())
		{
			floatingTask *ft=new floatingTask;
			ft->setter( description);
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
			if(i==userInput.size())
			{
				endTime=startTime;
				startTime='\0';
				DeadlineTask dt= new DeadlineTask;
				dt->setter(description,endTime);
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
				timedTask tt= new timedTask;
				tt->setter (description, startTime, endTime);
			}
		}
	}

tm CommandProcessor::stringToTime (string startTime)
{
	tm sTime;
	int index=0;
	int date=(startTime[index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	int month=(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	int year=(startTime[++index]-ASCII_VALUE_0)*1000+(startTime[++index]-ASCII_VALUE_0)*100+(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	sTime.tm_mday=date;
	sTime.tm_mon=month;
	sTime.tm_year=year;
	int hour=(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	int min=(startTime[++index]-ASCII_VALUE_0)*10+(startTime[++index]-ASCII_VALUE_0);
	sTime.tm_hour=hour;
	sTime.tm_min=min;
	return sTime;
}
