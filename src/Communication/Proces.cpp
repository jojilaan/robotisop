#include "Process.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

Process::Process(std::string name, int **FSM, int states)
{
	_name = name;
	_nstates = states;
	_FSM = FSM;
	_currentState = 0;
	//_sensitivityList = NULL;
}

Process::~Process()
{
}

void Process::addAlphabet(std::vector<std::string> alphabet)
{
	for (const auto alpha : alphabet)
	{
		_alphabet.push_back(alpha);
	}
	printAlphabet();
}

void Process::printAlphabet()
{
	for (const auto alpha : _alphabet)
	{
		std::cout << alpha << ' ';
	}
	std::cout << '\n';
}

std::vector<std::string> Process::getAlphabet()
{
	return _alphabet;
}

std::string Process::getName()
{
	return _name;
}

std::vector<std::string> Process::getSensitivityList()
{
	_sensitivityList.clear();
	for (int i = 0; i < _nstates; ++i)
	{

		if (_FSM[i][_currentState] != -1)
		{
			_sensitivityList.push_back(_alphabet.at(i));
		}
	}

	return _sensitivityList;
}

void Process::makeTransition(std::string trans)
{
	//kijk in statetable
	//verhoog current state
	// Find given element in vector
	auto it = std::find(_alphabet.begin(), _alphabet.end(), trans);
	int z; 
	if (it != _alphabet.end())
	{
		z = std::distance(_alphabet.begin(), it);
	}
	int nextState = _FSM[z][_currentState]; 
	//std::cout << " next state " << nextState << '\n';
	_currentState = nextState; 
	std::cout << " curentState " << _currentState << '\n';
}