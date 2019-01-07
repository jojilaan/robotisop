#ifndef PROCESS_H // include guard
#define PROCESS_H
#include <vector>
#include <map>
#include "CommunicationServer.hpp"
//c CommunicationServer; 

class Process
{
    public:
	Process(CommunicationServer communicationserver);
	~Process();
    void addAlphabet(std::vector<std::string> alpahbet);
	void addStates(std::vector<int> states);
    void printAlphabet();
    void printStates();
	
    
    private:
    std::vector<std::string> _alphabet;
    std::vector<int> _states;
	std::vector<std::string> _sensitivityList;
    CommunicationServer _communicationserver;
    CommunicationServer _a; 
};

#endif
