#include "Search.h"


void Search::setInputList(vector<Task*> list){

	Search::inputList = list;
}

vector<Task*> Search::getInputList(){
	return Search::inputList;
}
bool Search::executeSearch(string description){

	for(int i =  0; i < Search::inputList.size(); i++){
		if(strcmpi(Search::inputList[i]->getDesc().c_str(), description.c_str()) == 0){
			Search::searchResults.push_back(Search::inputList[i]);
			Search::resultIndices.push_back(i);
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