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
    createAlphabetTableHeader();
    createLookUpTable();
    fillLookUpTable();
}

void CommunicationServer::createAlphabetTableHeader()
{
    //add alphabet strings to first row of table
    _allActions.clear();
    std::cout << _vProcesses.size();
    for (int i = 0; static_cast<size_t>(i) < _vProcesses.size(); ++i)
    {
        std::vector<std::string> alphabet = _vProcesses.at(i).getAlphabet();

        for (int j = 0; static_cast<size_t>(j) < alphabet.size(); ++j)
        {
            if (std::find(_allActions.begin(), _allActions.end(), alphabet.at(j)) != _allActions.end())
            {
                continue;
            }
            else
            {
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
        std::vector<std::string> alphabet = _vProcesses.at(i).getAlphabet();
        for (int j = 0; static_cast<size_t>(j) < _allActions.size(); j++)
        {
            if (std::find(alphabet.begin(), alphabet.end(), _allActions.at(j)) != alphabet.end())
            {
                _lookUpTable[i][j] = '1';
            }
            else
            {
                _lookUpTable[i][j] = '0';
            }
        }
    }
    for (int i = 0; static_cast<size_t>(i) < _vProcesses.size(); i++)
    {
        for (int j = 0; static_cast<size_t>(j) < _allActions.size(); j++)
        {
            std::cout << _lookUpTable[i][j];
        }
        std::cout << "\n";
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

void CommunicationServer::getSensitiveLists()
{
    for (auto proc : _vProcesses)
    {
        _map[proc.getName()] = proc.getSensitivityList();
        // print
        //for(auto sL : _map[proc.getName()] )
        //{
        //    std::cout << "test  " << sL;
        //}
        //printf("\n");
    }
    //printf("\n");
}
