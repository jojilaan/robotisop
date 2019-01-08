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
	Process(std::string name, int **FSM, int states);
	//Process(std::string name, std::array<std::array<int, 3>, 3> stateTable);
	~Process();
	void addAlphabet(std::vector<std::string> alpahbet);
	void printAlphabet();
	std::string getName();
	std::vector<std::string> getAlphabet();
	std::vector<std::string> getSensitivityList();
	void makeTransition(std::string trans);


private:
	int **_FSM;
	int _currentState;
	int _nstates;
	std::vector<std::string> _alphabet;
	std::vector<std::string> _sensitivityList;
	std::string _name;
	std::map<int, std::string> _m;

};

#endif
