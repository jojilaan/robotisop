#include <iostream>
#include <thread>
#include "Process.hpp"
#include "CommunicationServer.hpp"

using namespace std;


int main()
{
  //Create communicationDriver
  //Create Procresses 
 // Process a;

  //a.GetData();
  //cout<<"HEY, you, I'm alive! Oh, and Hello World!\n";
  //cin.get();
  CommunicationServer communicationserver; 
  std::vector<std::string> alphabet;
  std::vector<int> stateTransition;
  alphabet.push_back("write");
	alphabet.push_back("read");
  
  stateTransition.push_back(1);
	stateTransition.push_back(-1);
	
  Process proc("Proc1");
  proc.addAlphabet(alphabet); 
  proc.addStates(stateTransition);
	printf("Alphabet\n");
  proc.printAlphabet();
  printf("State\n"); 
  proc.printStates(); 

  stateTransition.clear();
	stateTransition.push_back(-1);
	stateTransition.push_back(1);
  Process proc2("Proc2");
  proc2.addAlphabet(alphabet); 
  proc2.addStates(stateTransition);
  communicationserver.addProcess(proc); 
  communicationserver.addProcess(proc2); 
  communicationserver.printProcesses(); 
  //proc.push_back(proc);

  return 1;
}

