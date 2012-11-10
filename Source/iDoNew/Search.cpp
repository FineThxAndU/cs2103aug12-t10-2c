#include "Search.h"


void Search::setInputList(vector<Task*> list){

	Search::inputList = list;
}

vector<Task*> Search::getInputList(){
	return Search::inputList;
}
bool Search::executeSearch(string description){

	for(int i =  0; i < Search::inputList.size(); i++){
		if(strstr(Search::inputList[i]->getDesc().c_str(), description.c_str()) != NULL ){
			Search::searchResults.push_back(Search::inputList[i]);
			Search::resultIndices.push_back(i);
		}
	}
	return true;
}
bool Search::executeSearchTime(Task* query)
	{
	    tm* currentTime=query->getStart();
		currentTime->tm_sec=0;
		currentTime->tm_isdst=-1;
		currentTime->tm_wday=0;
		currentTime->tm_yday=0;
		currentTime->tm_hour=0;
		currentTime->tm_min=0;

	for(int i =  0; i < Search::inputList.size(); i++){
			
			//mktime(tempTime);
			if(Search::inputList[i]->getStart())
				{
				tm* tempTime= Search::inputList[i]->getStart();
				tempTime->tm_year-=1900;
				tempTime->tm_mon-=1;
				tempTime->tm_isdst=-1;
				tempTime->tm_wday=0;
				tempTime->tm_yday=0;
				tempTime->tm_sec=0;
				int tempHour=tempTime->tm_hour;
				tempTime->tm_hour=0;

				if(!difftime(mktime(tempTime),mktime(query->getStart())))
				{
				tempTime->tm_mon+=1;
				tempTime->tm_year+=1900;
				tempTime->tm_hour=tempHour;
				Search::searchResults.push_back(Search::inputList[i]);
				Search::resultIndices.push_back(i);
				}
				else
				{
					tempTime->tm_mon+=1;
					tempTime->tm_year+=1900;
					tempTime->tm_hour=tempHour;
				}
				
				}

			else if(Search::inputList[i]->getEnd())
				{
				tm* tempTime= Search::inputList[i]->getEnd();
				tempTime->tm_year-=1900;
				tempTime->tm_mon-=1;
				tempTime->tm_isdst=-1;
				tempTime->tm_wday=0;
				tempTime->tm_yday=0;
				tempTime->tm_sec=0;
				int tempHour=tempTime->tm_hour;
				tempTime->tm_hour=0;
				if(!difftime(mktime(tempTime),mktime(query->getStart())))
				{ 
				tempTime->tm_mon+=1;
				tempTime->tm_year+=1900;
				tempTime->tm_hour=tempHour;
				Search::searchResults.push_back(Search::inputList[i]);
				Search::resultIndices.push_back(i);
				}
				else
					{
					tempTime->tm_mon+=1;
					tempTime->tm_year+=1900;
					tempTime->tm_hour=tempHour;
					}
				
				}

			

	}
	return true;
	}
bool Search::executeSearch(Task* query){

	for(int i =  0; i < Search::inputList.size(); i++){
		if((Search::inputList[i]) == query){
			Search::searchResults.push_back(Search::inputList[i]);
			Search::resultIndices.push_back(i);
		}
}
	return true;
}
vector<int> Search::getIndices(){
	return Search::resultIndices;
}

vector<Task*> Search::getResults(){
	return Search::searchResults;
}

void Search::clearSearchResults(){

	Search::searchResults.clear();
	Search::resultIndices.clear();
}