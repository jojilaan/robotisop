#include "CommunicationServer.hpp"
#include "Process.hpp"


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



