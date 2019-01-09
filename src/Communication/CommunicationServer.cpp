#include "CommunicationServer.hpp"
#include "Process.hpp"
#include <iostream>
#include <algorithm>
#include <iterator> // std::iterator, std::input_iterator_tag

CommunicationServer::CommunicationServer()
{
	//std::vector<std::vector<int>> stateTable;
	//_stateTable.push_back(p);
}

CommunicationServer::~CommunicationServer()
{
}

void CommunicationServer::init()
{
	createAlphabetTableHeader();
	for(auto n : _allActions)
	{
		std::cout << "action " << ' ' << n;

	}
			std::cout << "\n ";

	createLookUpTable();
	fillLookUpTable();
}

void CommunicationServer::createAlphabetTableHeader()
{
	//add alphabet strings to first row of table
	_allActions.clear();

	//std::cout << _vProcesses.size();
	for (int i = 0; static_cast<size_t>(i) < _vProcesses.size(); ++i)
	{
		std::vector<std::string> alphabet = _vProcesses.at(i)->getAlphabet();

		for (int j = 0; static_cast<size_t>(j) < alphabet.size(); ++j)
		{
			if (std::find(_allActions.begin(), _allActions.end(), alphabet.at(j)) != _allActions.end())
			{
				continue;
			}
			else
			{
				_allActionsMap[alphabet.at(j)] = 0;
				_allActions.push_back(alphabet.at(j));
			}
		}
	}
}
void CommunicationServer::createLookUpTable()
{
	_lookUpTable = new char *[_vProcesses.size()];
	for (int i = 0; i < _vProcesses.size(); i++)
	{
		_lookUpTable[i] = new char[_allActions.size()];
	}
}

void CommunicationServer::fillLookUpTable()
{
	for (int i = 0; static_cast<size_t>(i) < _vProcesses.size(); i++)
	{
		std::vector<std::string> alphabet = _vProcesses.at(i)->getAlphabet();
		for (int j = 0; static_cast<size_t>(j) < _allActions.size(); j++)
		{
			if (std::find(alphabet.begin(), alphabet.end(), _allActions.at(j)) != alphabet.end())
			{
				_allActionsMap[_allActions.at(j)]++;
				_lookUpTable[i][j] = '1';
			}
			else
			{
				_lookUpTable[i][j] = '0';
			}
		}
	}
	//// print lookuptable
	for (int i = 0; static_cast<size_t>(i) < _vProcesses.size(); i++)
	{
		for (int j = 0; static_cast<size_t>(j) < _allActions.size(); j++)
		{
			std::cout << _lookUpTable[i][j];
		}
		std::cout << "\n";
	}
	// print allActionsMap
	//for (auto &x : _allActionsMap)
	//{
	//	std::cout << x.first << ": " << x.second << '\n';
	//}
	//for (int i=0; i< _allActions.size(); i++)
	//{
	//	std::cout << _allActions.at(i) << " jajajaj" <<  '\n';
	//}
}

std::vector<std::vector<int>> CommunicationServer::GetStateTable()
{
	return _stateTable;
}

void CommunicationServer::addProcess(Process *p)
{
	_vProcesses.push_back(p);
}

void CommunicationServer::printProcesses()
{
	for (auto proc : _vProcesses)
	{
		std::cout << proc->getName();
	}
	printf("\n");
}

void CommunicationServer::getSensitiveLists()
{
	for (auto proc : _vProcesses)
	{	
		std::vector<std::string> kp = proc->getSensitivityList();
		for(auto a:kp)
		{
			std::cout << proc->getName() << " has " << a; 
		}
		std::cout << "\n"; 
		_map[proc->getName()] = proc->getSensitivityList();
	}
	
}

void CommunicationServer::getNextPossibleActions()
{
	nextPossibleActions.clear();

	for (auto proc : _vProcesses)
	{
		for (auto s : proc->getSensitivityList())
		{
			//not found
			if (nextPossibleActions.find(s) == nextPossibleActions.end())
			{
				nextPossibleActions.insert(std::pair<std::string, int>(s, 1));
				//nextPossibleActions.insert(std::pair<std::string, int>("read", 1));
			}
			else //found in map
			{
				nextPossibleActions[s]++;
			}
		}
	}

	// print allActionsMap
	for (auto &x : nextPossibleActions)
	{
		std::cout << "next " << x.first << ": " << x.second << '\n';
	}
	for (auto it = nextPossibleActions.cbegin(); it != nextPossibleActions.cend() /* not hoisted */; /* no increment */)
	{
		std::cout << _allActionsMap.find(it->first)->second; 
		std::cout << _allActionsMap.find(it->first)->first; 
		std::cout << "\n"; 
		if (_allActionsMap.find(it->first)->second != it->second)
		{
			nextPossibleActions.erase(it);
		}
		++it;
	}
	for (auto &z : _allActionsMap)
	{
		std::cout << "All possible transitions: " << z.first << ' ' << z.second << '\n';
	}
	for (auto &x : nextPossibleActions)
	{
		std::cout << "Next possible transitions: " << x.first << '\n';
	}
}

void CommunicationServer::makeTransition(std::string trans)
{
	for (auto proc : _vProcesses)
	{
		std::vector<std::string> a = _map[proc->getName()];
		for (auto const &value : a)
		{
			if (value == trans)
			{
				std::cout << "Update " << proc->getName();
				proc->makeTransition(value);
			}
		}
	}
}