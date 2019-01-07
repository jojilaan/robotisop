#include "Process.hpp"
#include <iostream>

Process(std::string name, std::array<std::array<int, 2>, 2> stateTable)
{
	_name = name;
	_stateTable2d = stateTable;
	_currentState = 0;
}

Process(std::string name, std::array<std::array<int, 3>, 3> stateTable)
{
	_name = name;
	_stateTable = stateTable;
	_currentState = 0;
	//_a = communicationserver;
	//_alphabet.push_back("wrtie");
	//_alphabet.push_back("read");
	// commincationdriver
	// fsm
	// actions
	// sesitiveActions
	//
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
		printf("state: %d \n", _stateTable[i][_currentState]);
		if(_stateTable[i][_currentState] != -1)
		{
			_sensitivityList.push_back(_stateTable[i][_currentState]);
		}
	}

	return _stateTable;
}
