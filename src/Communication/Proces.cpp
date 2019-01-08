#include "Process.hpp"
#include <iostream>

Process::Process(std::string name, int **FSM, int states)
{
	_name = name;
	_nstates = states;
	_FSM = FSM;
	_currentState = 1;
	//_sensitivityList = NULL;
}

Process::~Process()
{
}

void Process::addAlphabet(std::vector<std::string> alphabet)
{
	for(const auto alpha : alphabet)
	{
		_alphabet.push_back(alpha);
	}

	// ADD to yourself
	//_alphabet = alphabet;
	//std::map<int, std::string> _m;
  //_m[1] = "Write man\n";
	//std::cout << _m[1];
	// Add to communicationServer;
	//_communicationserver.addAlphabet(_alphabet);
}

void Process::printAlphabet()
{
	// ADD to yourself
	for (const auto alpha : _alphabet)
	{
		std::cout << alpha << ' ';
		//printf("%s , ", alpha);
	}
	printf("\n");
}

std::string Process::getName()
{
	return _name;
}

std::vector<std::string> Process::getSensitivityList()
{
	_sensitivityList.clear();
	for (int i = 0; i < _nstates; i++)
	{
		//printf("state: %d \n", _FSM[i][_currentState]);
		if (_FSM[i][_currentState] != -1)
		{
			std::cout << _name << " is sensitive for: " <<_alphabet[i] << '\n';
			//_sensitivityList.push_back(_stateTable[i][_currentState]);

			_sensitivityList.push_back(_alphabet[i]);
		}
	}

	return _sensitivityList;
}
