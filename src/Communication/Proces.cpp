#include "Process.hpp"
#include <iostream>

Process::Process(std::string name,  int** stateTable, int states)
{
	_name = name;
    _states = states;
    _stateTable = stateTable; 
	_currentState = 0;
    //_sensitivityList = NULL;
}

Process::~Process()
{
}

void Process::addAlphabet(std::vector<std::string> alphabet)
{
	// ADD to yourself
	_alphabet = alphabet;
    //std::map<int, std::string> _m; 
    _m[1] = "Write man\n"; 
    //std::cout << _m[1]; 
	// Add to communicationServer;
	//_communicationserver.addAlphabet(_alphabet);
}

void Process::printAlphabet()
{
	// ADD to yourself
	for (const auto alpha : _alphabet)
	{
		std::cout <<  alpha << ' ';
		//printf("%s , ", alpha);
	}
	printf("\n");
}

std::string Process::getName()
{
	return _name;
}

std::vector<int> Process::getSensitivityList()
{
	_sensitivityList.clear();
	for(int i = 0; i < _states; i++)
	{
		printf("state: %d \n", _stateTable[i][_currentState]);
		if(_stateTable[i][_currentState] != -1)
		{
            std::cout << "hashmap " <<_m[_stateTable[i][_currentState]]; 
			_sensitivityList.push_back(_stateTable[i][_currentState]);
		}
	}

	return _sensitivityList;
}
