#ifndef PROCESS_H // include guard
#define PROCESS_H
#include <vector>
#include <map>
class CommunicationServer; 
//#include "CommunicationServer.hpp"
//c CommunicationServer; 

class Process
{
    public:
	Process(std::string name);
	~Process();
    void addAlphabet(std::vector<std::string> alpahbet);
	void addStates(std::vector<int> states);
    void printAlphabet();
    void printStates();
	std::string getName();

    
    private:
    std::vector<std::string> _alphabet;
    std::vector<int> _states;
	std::vector<std::string> _sensitivityList;
    std::string _name;
};

#endif
