#ifndef PROCESS_H // include guard
#define PROCESS_H
#include <vector>
#include <map>
#include "CommunicationServer.hpp"



class Process
{

	Process(std::vector<std::vector<int>> fsm);
	~Process();

	public:

	private:
    CommunicationServer communicationServer;
		std::vector<std::string> alphabet;
		std::vector<std::string> sensitivityList;


}

#endif
