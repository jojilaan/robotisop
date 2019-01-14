#include "CommunicationServer.hpp"
#include "Process.hpp"
#include <iostream>
#include <algorithm>
#include <iterator> // std::iterator, std::input_iterator_tag

CommunicationServer::CommunicationServer() : _hds("/dev/ttyUSB0")
{
	//initialize the Hardware Dependend Software
	_hds.init();
	//Move to begin position
	_hds.beginPosition();
}

CommunicationServer::~CommunicationServer()
{
}

void CommunicationServer::init()
{
	//Initialize the complete alphabet
	createAlphabetTableHeader();
	//count the total number per alphabet action and map them
	fillActionMap();
}

void CommunicationServer::createAlphabetTableHeader()
{
	//make sure the vector is empty
	_allActions.clear();

	//loop throug every known process
	for (auto &proc : _vProcesses)
	{
		for (auto &alpha : proc->getAlphabet())
		{
			//if the actoin aleardy exist in the complete alphabet continue. if it doesn't map this action and add
			//to the complete alphabet
			if (std::find(_allActions.begin(), _allActions.end(), alpha) != _allActions.end())
			{
				continue;
			}
			else
			{
				_allActionsMap[alpha] = 0;
				_allActions.push_back(alpha);
			}
		}
	}
}

void CommunicationServer::fillActionMap()
{
	//loop throug every known process
	for (auto &proc : _vProcesses)
	{
		//get the alphabet of the current process
		std::vector<std::string> alphabet = proc->getAlphabet();
		for (auto &action : _allActions)
		{
			//if the current action is found in the alphabet of the process count up the total number of times
			//it apears in the allactions map
			//this is done to know how many processes have this action. and used to synchronize.
			if (std::find(alphabet.begin(), alphabet.end(), action) != alphabet.end())
			{
				_allActionsMap[action]++;
			}
		}
	}
}

void CommunicationServer::addProcess(Process *p)
{
	_vProcesses.push_back(p);
}

void CommunicationServer::printProcesses()
{
	//for debugging purposes
	for (auto proc : _vProcesses)
	{
		std::cout << proc->getName();
	}
	printf("\n");
}

void CommunicationServer::getSensitiveLists()
{
	//getthe sensitivity lists from all processes and map them.
	for (auto proc : _vProcesses)
	{
		_mSensitivityLists[proc->getName()] = proc->getSensitivityList();
	}
}

std::vector<std::string> CommunicationServer::getNextPossibleActions()
{
	nextPossibleActions.clear();

	//loop trough all processes
	for (auto proc : _vProcesses)
	{
		//
		for (auto s : _mSensitivityLists[proc->getName()])
		{
			//if not found insert into next possible actions list
			if (nextPossibleActions.find(s) == nextPossibleActions.end())
			{
				nextPossibleActions.insert(std::pair<std::string, int>(s, 1));
			}
			else //else count up number of occurrences
			{
				nextPossibleActions[s]++;
			}
		}
	}

	//if the total number of occurrences match the number of occurrences in the allactions map this action is possible.
	for (auto it = nextPossibleActions.begin(); it != nextPossibleActions.end();)
	{
		if (_allActionsMap.find(it->first)->second != it->second)
		{
			it = nextPossibleActions.erase(it);
		}
		else
		{
			++it;
		}
	}

  //print out the next possible actions and return the list.
	std::vector<std::string> list;
	std::cout << "Next possible transitions:[ ";
	for (auto &x : nextPossibleActions)
	{
		list.push_back(x.first);
		std::cout << x.first << ' ';
	}
	std::cout << " ]\n";
	return list;
}

void CommunicationServer::makeTransition(std::string requestedAction)
{
	//check if the action is possible and update every sensetive process
	bool peformed = false;
	for (auto proc : _vProcesses)
	{
		for (auto const &sensitiveAction : _mSensitivityLists[proc->getName()])
		{
			if (sensitiveAction == requestedAction)
			{
				proc->makeTransition(sensitiveAction);
				peformed = true;
			}
		}
	}

	//if the requested action was peformed, let the hardware pefrom this action
	if(peformed)
	{
		_hds.makeTransition(requestedAction);
	}
}
