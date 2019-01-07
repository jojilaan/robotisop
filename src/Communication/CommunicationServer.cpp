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
    for(auto proc : _vProcesses)
    {
        std::cout << proc.getName(); 
        //printf("%s, ", alpha);
    }
    printf("\n");
} 

