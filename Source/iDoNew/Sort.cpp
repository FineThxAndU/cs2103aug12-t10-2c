#include "Sort.h"


Sort::Sort(){

	Sort::order = 'a';
	Sort::criteria = "time";
}

void Sort::setInputList(vector<Task*> list){

	Sort::inputList = list;
}

void Sort::setCriteria(string criteria){

	Sort::criteria = criteria.c_str();
}

void Sort::setOrder(char order){

	Sort::order = order;
}

void Sort::executeSort(){

	if(strcmpi(Sort::criteria.c_str(), "time") == 0){
		if(tolower(Sort::order) == 'a')
			sortByTimeAsc();
		else if(tolower(Sort::order) == 'd')
				sortByTimeDesc();
	}
	else if(strcmpi(Sort::criteria.c_str(), "description") == 0){
			if(tolower(Sort::order) == 'a')
				Sort::sortByDescripAsc();
			else if(tolower(Sort::order) == 'd')
					Sort::sortByDescripDesc();
	}
}

void Sort::sortByDescripAsc(){

	for(int i = 0; i < Sort::inputList.size() - 1; i++){
		for(int j = 0; j < Sort::inputList.size() - 1 - i; j++){
			if(strcmpi(Sort::inputList[j]->getDesc().c_str(), Sort::inputList[j + 1]->getDesc().c_str()) > 0) {
				Task *temp = Sort::inputList[j];
				Sort::inputList[j] = Sort::inputList[j + 1];
				Sort::inputList[j + 1] = temp;
			}
		}
	}
}

void Sort::sortByDescripDesc(){

	for(int i = 0; i < Sort::inputList.size() - 1; i++){
		for(int j = 0; j < Sort::inputList.size() - 1 - i; j++){
			if(strcmpi(Sort::inputList[j]->getDesc().c_str(), Sort::inputList[j + 1]->getDesc().c_str()) < 0) {
				Task *temp = Sort::inputList[j];
				Sort::inputList[j] = Sort::inputList[j + 1];
				Sort::inputList[j + 1] = temp;
			}
		}
	}
}

void Sort::sortByTimeAsc(){
	for(int i = 0; i < Sort::inputList.size() - 1; i++){
		for(int j = 0; j < Sort::inputList.size() - 1 - i; j++){
			if(Sort::inputList[j]->getEnd() > Sort::inputList[j+1]->getEnd()) {
				Task *temp = Sort::inputList[j];
				Sort::inputList[j] = Sort::inputList[j + 1];
				Sort::inputList[j + 1] = temp;
			}
		}
	}
}

void Sort::sortByTimeDesc(){
	for(int i = 0; i < Sort::inputList.size() - 1; i++){
		for(int j = 0; j < Sort::inputList.size() - 1 - i; j++){
			if(Sort::inputList[j]->getEnd() < Sort::inputList[j+1]->getEnd()) {
				Task *temp = Sort::inputList[j];
				Sort::inputList[j] = Sort::inputList[j + 1];
				Sort::inputList[j + 1] = temp;
			}
		}
	}
}

bool operator > (tm t1, tm t2){

	if(t1.tm_year > t2.tm_year)
		return true;
	else if(t1.tm_mon > t2.tm_mon)
		return true;
	else if(t1.tm_mday > t2.tm_mday)
		return true;
	else if(t1.tm_hour >t2.tm_hour)
		return true;
	else if(t1.tm_min >t2.tm_min)
		return true;
	else if(t1.tm_sec >t2.tm_sec)
		return true;
	else
		return false;
}

bool operator < (tm t1, tm t2){

	if(t1.tm_year < t2.tm_year)
		return true;
	else if(t1.tm_mon < t2.tm_mon)
		return true;
	else if(t1.tm_mday < t2.tm_mday)
		return true;
	else if(t1.tm_hour < t2.tm_hour)
		return true;
	else if(t1.tm_min < t2.tm_min)
		return true;
	else if(t1.tm_sec < t2.tm_sec)
		return true;
	else
		return false;
}