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

int **LSchouderP;
int **RSchouderP;
int **LSchouderR;
int **RSchouderR;
int **Lelleboog;
int **Relleboog;
int **LeftToReady;
int **RightToReady;

void initProcs()
{
	// arr ProcA //////////////////
	LSchouderP = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		LSchouderP[i] = new int[2];
	}
	LSchouderP[0][0] = 1;
	LSchouderP[0][1] = -1;
	LSchouderP[1][0] = -1;
	LSchouderP[1][1] = 0;

	RSchouderP = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		RSchouderP[i] = new int[2];
	}
	RSchouderP[0][0] = 1;
	RSchouderP[0][1] = -1;
	RSchouderP[1][0] = -1;
	RSchouderP[1][1] = 0;

	LSchouderR = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		LSchouderR[i] = new int[2];
	}
	LSchouderR[0][0] = 1;
	LSchouderR[0][1] = -1;
	LSchouderR[1][0] = -1;
	LSchouderR[1][1] = 0;

	RSchouderR = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		RSchouderR[i] = new int[2];
	}
	RSchouderR[0][0] = 1;
	RSchouderR[0][1] = -1;
	RSchouderR[1][0] = -1;
	RSchouderR[1][1] = 0;

	Lelleboog = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		Lelleboog[i] = new int[2];
	}
	Lelleboog[0][0] = 1;
	Lelleboog[0][1] = -1;
	Lelleboog[1][0] = -1;
	Lelleboog[1][1] = 0;

	Relleboog = new int *[2];
	for (int i = 0; i < 2; i++)
	{
		Relleboog[i] = new int[2];
	}
	Relleboog[0][0] = 1;
	Relleboog[0][1] = -1;
	Relleboog[1][0] = -1;
	Relleboog[1][1] = 0;

	LeftToReady = new int *[6];
	for (int i = 0; i < 6; i++)
	{
		LeftToReady[i] = new int[7];
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			LeftToReady[i][j] = -1;
		}
	}

	LeftToReady[0][0] = 1;
	LeftToReady[1][1] = 2;
	LeftToReady[2][2] = 3;
	LeftToReady[2][3] = 4;
	LeftToReady[3][4] = 0;
	LeftToReady[4][5] = 5;
	LeftToReady[5][6] = 2;

	RightToReady = new int *[6];
	for (int i = 0; i < 6; i++)
	{
		RightToReady[i] = new int[7];
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			RightToReady[i][j] = -1;
		}
	}

	RightToReady[0][0] = 1;
	RightToReady[1][1] = 2;
	RightToReady[2][2] = 3;
	RightToReady[2][3] = 4;
	RightToReady[3][4] = 0;
	RightToReady[4][5] = 5;
	RightToReady[5][6] = 2;
}

int main()
{

	CommunicationServer communicationserver;
	srand(time(NULL));

	initProcs();
	std::vector<Process> procs;
	std::vector<std::string> alphabet;
	std::vector<std::string> procAlphabet;
	std::vector<std::string> sensitivityList;
	alphabet.push_back("ShoulderRInPosition"); // 0
	alphabet.push_back("ShoulderPInPosition"); // 1
	alphabet.push_back("ShoulderPOutPosition"); // 2
	alphabet.push_back("Execute"); // 3
	alphabet.push_back("ShoulderROutPosition"); // 4
	alphabet.push_back("ElbowInPosition"); // 5
	alphabet.push_back("ElbowOutPosition"); // 6


	/* proc1 begin */
	Process proc("LSchouderP", LSchouderP, 2);
	procAlphabet.push_back("left." + alphabet.at(1));
	procAlphabet.push_back("left." + alphabet.at(2));
	proc.addAlphabet(procAlphabet);
	procs.push_back(proc);
	procAlphabet.clear();
	/* proc1 end */

	/* proc2 begin */
	Process proc2("RSchouderP", RSchouderP, 2);
	procAlphabet.push_back("right." + alphabet.at(1));
	procAlphabet.push_back("right." + alphabet.at(2));
	proc2.addAlphabet(procAlphabet);
	procs.push_back(proc2);
	procAlphabet.clear();
	/* proc2 begin */

	/* proc3 begin */
	Process proc3("LSchouderR", LSchouderR, 2);
	procAlphabet.push_back("left." + alphabet.at(0));
	procAlphabet.push_back("left." + alphabet.at(4));
	proc3.addAlphabet(procAlphabet);
	procs.push_back(proc3);
	procAlphabet.clear();
	/* proc3 begin */

	/* proc4 begin */
	Process proc4("RSchouderR", RSchouderR, 2);
	procAlphabet.push_back("right." + alphabet.at(0));
	procAlphabet.push_back("right." + alphabet.at(4));
	proc4.addAlphabet(procAlphabet);
	procs.push_back(proc4);
	procAlphabet.clear();
	/* proc4 begin */

	/* proc5 begin */
	Process proc5("Lelleboog", Lelleboog, 2);
	procAlphabet.push_back("left." + alphabet.at(5));
	procAlphabet.push_back("left." + alphabet.at(6));
	proc5.addAlphabet(procAlphabet);
	procs.push_back(proc5);
	procAlphabet.clear();
	/* proc5 begin */

	/* proc6 begin */
	Process proc6("Relleboog", Relleboog, 2);
	procAlphabet.push_back("right." + alphabet.at(5));
	procAlphabet.push_back("right." + alphabet.at(6));
	proc6.addAlphabet(procAlphabet);
	procs.push_back(proc6);
	procAlphabet.clear();
	/* proc6 begin */

	/* proc7 begin */
	Process proc7("LeftToReady", LeftToReady, 6);
	procAlphabet.push_back("left." + alphabet.at(0));
	procAlphabet.push_back("left." + alphabet.at(1));
	procAlphabet.push_back("left." + alphabet.at(2));
	procAlphabet.push_back("left." + alphabet.at(3));
	procAlphabet.push_back("left." + alphabet.at(4));
	procAlphabet.push_back("left." + alphabet.at(5));
	procAlphabet.push_back("left." + alphabet.at(6));
	proc7.addAlphabet(procAlphabet);
	procs.push_back(proc7);
	procAlphabet.clear();
	/* proc7 begin */

	/* proc8 begin */
	Process proc8("RightToReady", RightToReady, 6);
	procAlphabet.push_back("right." + alphabet.at(0));
	procAlphabet.push_back("right." + alphabet.at(1));
	procAlphabet.push_back("right." + alphabet.at(2));
	procAlphabet.push_back("right." + alphabet.at(3));
	procAlphabet.push_back("right." + alphabet.at(4));
	procAlphabet.push_back("right." + alphabet.at(5));
	procAlphabet.push_back("right." + alphabet.at(6));
	proc8.addAlphabet(procAlphabet);
	procs.push_back(proc8);
	procAlphabet.clear();
	/* proc8 begin */


	for (auto &proc : procs)
	{
		communicationserver.addProcess(&proc);
	}
	communicationserver.init();
	communicationserver.getSensitiveLists();
	sensitivityList = communicationserver.getNextPossibleActions();

	// start loop here
	while (true)
	{
		// enter number
		std::string input = "";
		std::cout << "Please enter an string value: ";
		getline(std::cin, input);
		if (input == "q") {
			return 1;
		}
		// make transistion
		//choose random if no input else at number;
		if(input == "")
			input =	sensitivityList.at(rand() % sensitivityList.size());
		else
		{
			int in = atoi(input.c_str());
			if(in > 0 && in < sensitivityList.size())
			{
				input = sensitivityList.at(in-1);
			}
		}

		//try to make rquested transition
		communicationserver.makeTransition(input);
		//get the new sensitivity list
		communicationserver.getSensitiveLists();

		//communicationserver.getNextPossibleActions();
		// getNextPossibleActions()
		sensitivityList.clear();
		sensitivityList = communicationserver.getNextPossibleActions();
	}

	return 1;
}
