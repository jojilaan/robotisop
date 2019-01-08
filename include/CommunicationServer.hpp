// my_class.h
#ifndef COMMUNICATIONSERVER_H // include guard
#define COMMUNICATIONSERVER_H
#include <vector>
#include <map>
#include "Process.hpp"

class CommunicationServer
{
public:
	CommunicationServer();
	~CommunicationServer();
	void addAlphabet(std::vector<std::string>);
	void addProcess(Process p);
	void printProcesses();
	void nextState(int);
	void init();

	std::vector<std::vector<int>> GetStateTable();
	std::string test;

private:
	std::vector<std::vector<std::string>> _alphabetTable;
	std::vector<Process> _vProcesses;
	std::vector<std::vector<int>> _stateTable;

	void createAlphabetTable();
	void fillAlphabetTable();
};

#endif /* MY_CLASS_H */
