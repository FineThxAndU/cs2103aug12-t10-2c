#include "GUI.h"
#include<fstream>
#include"Task.h"
#include<iostream>

using namespace std;

void GUI:: writeToOutput(vector<Task*>introList)
{
	ofstream fileObj;
	fileObj.open(inputFileName);
	for(int i=0;i<introList.size();i++)
	{
		fileObj << introList[i]->getDesc()<<endl;
		fileObj<<asctime(introList[i]->getStart())<<endl;
		fileObj<<asctime(introList[i]->getEnd())<<endl;
	}
	fileObj.close();
}
GUI::GUI()
{
	inputFileName="Input.txt";
	outputFileName="text2.txt";
}

string GUI::readUserInput()
{
	ifstream fr(outputFileName);
	char s[100],s1[100];
	while(fr.getline(s,100))
	{
		if(strcmp(s,"\0"))
			strcpy(s1,s);
	}
	string userInput;
	if(strcmp(s1,"\0"))
	userInput=s1;
	fr.close();
	return userInput;
}