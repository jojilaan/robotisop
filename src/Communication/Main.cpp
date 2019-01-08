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
	arrProcB = new int *[3];
	for (int i = 0; i < 3; i++)
	{
		arrProcB[i] = new int[3];
	}
	arrProcB[0][0] = 1;
	arrProcB[0][1] = -1;
	arrProcB[0][2] = -1;
	arrProcB[1][0] = -1;
	arrProcB[1][1] = 2;
	arrProcB[1][2] = -1;
	arrProcB[2][0] = -1;
	arrProcB[2][1] = -1;
	arrProcB[2][2] = 0;
	// arr ProcB //////////////////
}

int main()
{
	CommunicationServer communicationserver;
	std::vector<std::string> alphabet;
	alphabet.push_back("write");
	alphabet.push_back("read");

	initProcs();

	Process proc("proca", arrProcA, 2);
	proc.addAlphabet(alphabet);
	//printf("Alphabet:\n");
	//proc.printAlphabet();

	alphabet.push_back("b.wait");
	Process proc2("Proc2", arrProcB, 3);
	proc2.addAlphabet(alphabet);

	communicationserver.addProcess(proc);
	communicationserver.addProcess(proc2);

	communicationserver.init();
	communicationserver.getSensitiveLists();
	communicationserver.getNextPossibleActions();

	// start loop here
	//while (true)
	//{
		
		// enter number 
		int i;
		std::cout << "Please enter an integer value: ";
		std::cin >> i;
		// make transistion 
		communicationserver.makeTransition("write");
		communicationserver.getSensitiveLists();
		// getNextPossibleActions()
		communicationserver.getNextPossibleActions();
	//}

	return 1;
}
