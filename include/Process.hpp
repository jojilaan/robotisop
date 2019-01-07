#ifndef PROCESS_H // include guard
#define PROCESS_H
#include <vector>
#include <map>
class CommunicationServer;
//#include "CommunicationServer.hpp"
//c CommunicationServer;

/*enum class alphabet
{
	WRITE,
	READ,
	BW
};
*/ 

class Process
{
public:
	Process(std::string name, int** test, int row);
	//Process(std::string name, std::array<std::array<int, 3>, 3> stateTable);
	~Process();
	void addAlphabet(std::vector<std::string> alpahbet);
	//void addStates(std::vector<int> states);
	void printAlphabet();
	//void printStates();
	std::string getName();
	std::vector<int> getSensitivityList();

private:
	std::vector<std::string> _alphabet;
	//int _stateTable2d[2][2];
    int** _stateTable; 
	//std::array<std::array<int, 3>, 3> _stateTable3d;
	std::string _name;
	int _currentState;
	std::vector<int> _sensitivityList;
    //std::vector<int> _states; 
    int _states;
    std::map<int, std::string> _m;
};

#endif
