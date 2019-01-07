#include "Process.hpp"
#include <iostream>

Process::Process(std::string name, int table[2][2])
{
	_name = name;
    for(int i = 0; i< 2; i++){
        for(int j = 0; j<2; j++){
             _stateTable2d[i][j] = table[i][j];
        }
       
    }
	//_stateTable2d = table;
	_currentState = 0;
}


Process::~Process()
{
}

void Process::addAlphabet(std::vector<std::string> alphabet)
{
	// ADD to yourself
	_alphabet = alphabet;
	// Add to communicationServer;
	//_communicationserver.addAlphabet(_alphabet);
}

void Process::addStates(std::vector<int> states)
{
	// ADD to yourself
	_states = states;
}

void Process::printAlphabet()
{
	// ADD to yourself
	for (const auto alpha : _alphabet)
	{
		std::cout << alpha;
		//printf("%s, ", alpha);
	}
	printf("\n");
}

void Process::printStates()
{
	// ADD to yourself
	for (const auto state : _states)
	{
		printf("%d, ", state);
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
	for(int i = 0; i < 2; i++)
	{
		printf("state: %d \n", _stateTable2d[i][_currentState]);
		if(_stateTable2d[i][_currentState] != -1)
		{
			_sensitivityList.push_back(_stateTable2d[i][_currentState]);
		}
	}

	return _sensitivityList;
}
