#ifndef GUI_H_
#define GUI_H_
#include<iostream>
#include<string.h>
#include "Task.h"
#include<vector>
using namespace std;
 class GUI
 {
	private:
		string inputFileName;
		string outputFileName;
	//fstream fr;
	//ofstream fw;
 public:
	 GUI();
	 void writeToOutput(vector<Task*>);
	 string readUserInput();
 };
#endif