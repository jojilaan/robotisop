// my_class.h
#ifndef COMMUNICATIONSERVER_H // include guard
#define COMMUNICATIONSERVER_H
#include <vector>
#include <unordered_map>
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
	void getSensitiveLists();
	std::vector<std::vector<int>> GetStateTable();

private:
	std::vector<std::string> _allActions;
	std::vector<Process> _vProcesses;
	std::vector<std::vector<int>> _stateTable;
    char **_lookUpTable;
	std::unordered_map<std::string, std::vector<std::string>> _map;

	void createAlphabetTableHeader();
	void fillLookUpTable();
	void createLookUpTable();
	


};

#endif /* MY_CLASS_H */
