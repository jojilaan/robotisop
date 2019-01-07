#include "CommunicationServer.hpp"


CommunicationServer::CommunicationServer()
{
	std::vector<std::vector<int>> stateTable;
	std::vector<int> p;

	p.push_back(1);
	p.push_back(-1);
	stateTable.push_back(p);
	p.clear();
	p.push_back(-1);
	p.push_back(1);
	stateTable.push_back(p);

	process.push_back(Process(stateTable));
}

CommunicationServer::~CommunicationServer()
{

}


