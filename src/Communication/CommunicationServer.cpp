#include "CommunicationServer.hpp"
#include "Process.hpp"
#include <iostream>
#include <algorithm>

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
    createAlphabetTable();
    fillAlphabetTable();
}

void CommunicationServer::createAlphabetTable()
{
    //add alphabet strings to first row of table
    _alphabetTable.clear();
    std::cout << _vProcesses.size();
    for (int i = 0; static_cast<size_t>(i) < _vProcesses.size(); ++i)
    {
        std::vector<std::string> alphabet = _vProcesses.at(i).getAlphabet();

        if (_alphabetTable.empty())
        {
            _alphabetTable.push_back(alphabet);
            continue;
        }
        else
        {
            for (int j = 0; static_cast<size_t>(j) < alphabet.size(); ++j)
            {
                if (std::find(_alphabetTable.begin(), _alphabetTable.end(), alphabet.at(j)) != _alphabetTable.end())
                {
                    continue;
                }
                else
                {
                    _alphabetTable.push_back(alphabet.at(j));
                }


            }
        }
    }
}

void CommunicationServer::fillAlphabetTable()
{
		for (int i = 0; static_cast<size_t>(i) < _vProcesses.size(); ++i)
    {
        std::vector<std::string> alphabet = _vProcesses.at(i).getAlphabet();



		}




    //print
    for (int i = 0; static_cast<size_t>(i) < _alphabetTable.size(); i++)
    {
        for (int j = 0; static_cast<size_t>(j) < _alphabetTable.at(i).size(); j++)
        {
            std::cout << _alphabetTable.at(i).at(j) << " ";
        }
        std::cout << '\n';
    }
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
