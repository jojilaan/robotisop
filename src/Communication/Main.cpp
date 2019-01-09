#include <iostream>
#include <thread>
#include "Process.hpp"
#include "CommunicationServer.hpp"

//using namespace std;

enum class states
{
	WRITE = 1,
	READ,
	BW,
	ERROR = -1
};

int **arrProcA;
int **arrProcB;
void initProcs()
{
	// arr ProcA //////////////////
	arrProcA = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		arrProcA[i] = new int[2];
	}
	arrProcA[0][0] = 1;
	arrProcA[0][1] = -1;
	arrProcA[1][0] = -1;
	arrProcA[1][1] = 0;
	// arr ProcA //////////////////
	// arr ProcB //////////////////
	arrProcB = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		arrProcB[i] = new int[2];
	}
	arrProcB[0][0] = 1;
	arrProcB[0][1] = -1;
	arrProcB[1][0] = -1;
	arrProcB[1][1] = 0;
	// arr ProcB //////////////////

}

int main()
{
	CommunicationServer communicationserver;
	std::vector<std::string> alphabet;
	alphabet.push_back("make");
	alphabet.push_back("ready");

	initProcs();
	//maybe alphabet.size() can be buggy, need research 
	Process proc("Maker", arrProcA, alphabet.size());
	proc.addAlphabet(alphabet);
	//printf("Alphabet:\n");
	//proc.printAlphabet();
	alphabet.clear();
	alphabet.push_back("ready");
	alphabet.push_back("use");
	Process proc2("User", arrProcB, alphabet.size());
	proc2.addAlphabet(alphabet);

	communicationserver.addProcess(&proc);
	communicationserver.addProcess(&proc2);

	communicationserver.init();
	communicationserver.getSensitiveLists();
	communicationserver.getNextPossibleActions();

	// start loop here
	while (true)
	{	
		// enter number 
		std::string input = ""; 
		std::cout << "Please enter an string value: ";
		getline(std::cin, input); 
		//std::cin >> i;
		// make transistion 
		//std::cout << input; 
		communicationserver.makeTransition(input);
		communicationserver.getSensitiveLists();

		// getNextPossibleActions()
		communicationserver.getNextPossibleActions();
	}

	return 1;
}
