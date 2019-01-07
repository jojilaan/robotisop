#ifndef PROCESS_H // include guard
#define PROCESS_H
#include <vector>
#include <map>
class CommunicationServer;
//#include "CommunicationServer.hpp"
//c CommunicationServer;

enum alphabet
{
	WRITE,
	READ;
	BW;
};

class Process
{
public:
	Process(std::string name, std::array<std::array<int, 2>, 2> stateTable);
	Process(std::string name, std::array<std::array<int, 3>, 3> stateTable);
	~Process();
	void addAlphabet(std::vector<std::string> alpahbet);
	void addStates(std::vector<int> states);
	void printAlphabet();
	void printStates();
	std::string getName();
	std::vector<int> getSensitivityList();

private:
	std::vector<std::string> _alphabet;
	std::array<std::array<int, 2>, 2> _stateTable2d;
	std::array<std::array<int, 3>, 3> _stateTable3d;
	std::string _name;
	int _currentState;
	vector<int> _sensitivityList;
};

#endif
