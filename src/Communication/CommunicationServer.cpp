#include "CommunicationServer.hpp"
#include "Process.hpp"
#include <iostream>

CommunicationServer::CommunicationServer()
{
	//std::vector<std::vector<int>> stateTable;
	//_stateTable.push_back(p);
}

CommunicationServer::~CommunicationServer()
{
}

void init()
{
	createAlphabetTable();
	fillAlphabetTable();
}

void createAlphabetTable()
{
	//add alphabet strings to first row of table
	alphabetTable.clear();
	for (int i = 0; i < _vProcesses.size(); ++i)
	{
		std::vector<std::string> alphabet = _vProcesses.at(i).getAlphabet();

		if (_alphabetTable.empty())
		{
			_alphabetTable.push_back(alphabet);
			continue;
		}
		else
		{
			for (int j = 0; j < alphabet.size(); ++j)
			{
				if (alphabet.at(j) == _alphabetTable.at(0).at(j))
				{
					continue;
				}
				else
				{
					_alphabetTable.at(0).push_back(alphabet.at(j));
				}
			}

		}
	}
}

void fillAlphabetTable
{

}

std::vector<std::vector<int>> CommunicationServer::GetStateTable()
{
	return _stateTable;
}

void CommunicationServer::addAlphabet(std::vector<std::string> alphabet)
{
}

void CommunicationServer::addProcess(Process p)
{
	_vProcesses.push_back(p);
}

void CommunicationServer::printProcesses()
{
	// ADD to yourself
	for (auto proc : _vProcesses)
	{
		std::cout << proc.getName();
		//printf("%s, ", alpha);
	}
	printf("\n");
}
