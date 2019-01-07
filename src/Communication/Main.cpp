#include <iostream>
#include <thread>
#include "Process.hpp"

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
	
  Process proc(communicationserver);
  proc.addAlphabet(alphabet); 
  proc.addStates(stateTransition);
	printf("Alphabet\n");
  proc.printAlphabet();
  printf("State\n"); 
  proc.printStates(); 

  stateTransition.clear();
	stateTransition.push_back(-1);
	stateTransition.push_back(1);
  
  //proc.push_back(proc);


  return 1;
}
