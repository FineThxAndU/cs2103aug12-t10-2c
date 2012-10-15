#include <iostream>
#include <string>
#include <vector>
#include "task.h"
#include <time.h>

using namespace std;

class CommandProcessor
{
public:
	vector<int> intProcessor (string);
	string cmdProcessor (string, Task*);
	void descProcessor (string, Task*);
	tm stringToTime (string);





};