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
int **Sync;

int main()
{
  //Create communicationDriver
  //Create Procresses
  // Process a;

  //a.GetData();
  //cout<<"HEY, you, I'm alive! Oh, and Hello World!\n";
  //cin.get();

  // arr ProcA //////////////////
  arrProcA= new int*[2]; 
  for(int i=0; i<2; i++){
    arrProcA[i] = new int[2]; 
  }
  arrProcA[0][0] = 1; 
  arrProcA[0][1] = -1; 
  arrProcA[1][0] = -1; 
  arrProcA[1][1] = 0; 
  // arr ProcA //////////////////
// vies
  const char* states_text[] = {"Write", "Read", "b.Wait"};
//
// arr ProcB //////////////////
  arrProcB= new int*[3]; 
  for(int i=0; i<3; i++){
    arrProcB[i] = new int[2]; 
  }
  arrProcB[0][0] =  1; 
  arrProcB[0][1] = -1;
  arrProcB[0][2] = -1; 
  arrProcB[1][0] = -1; 
  arrProcB[1][1] =  2; 
  arrProcB[1][2] = -1;
  arrProcB[2][0] = -1; 
  arrProcB[2][1] = -1; 
  arrProcB[2][2] =  0;
  // arr ProcB //////////////////
// arr Sync //////////////////
  Sync= new int*[3]; 
  for(int i=0; i<3; i++){
    Sync[i] = new int[2]; 
  }
  Sync[0][0] =  1; 
  Sync[0][1] = -1;
  Sync[0][2] = -1; 
  Sync[1][0] = -1; 
  Sync[1][1] =  2; 
  Sync[1][2] = -1;
  Sync[2][0] = -1; 
  Sync[2][1] = -1; 
  Sync[2][2] =  0;
  // arr Sync //////////////////
  //std::array<std::array<int, 3>, 3> procb = {{{1, -1, -1}, {-1, 2, -1}, {-1, -1, 0}}};

  CommunicationServer communicationserver;
  std::vector<std::string> alphabet;
  std::vector<int> stateTransition;
  alphabet.push_back("write");
  alphabet.push_back("read");

  stateTransition.push_back(1);
  stateTransition.push_back(-1);
  Process proc("proca", arrProcA, 2);
  proc.addAlphabet(alphabet);
  //proc.addStates(stateTransition);
  printf("Alphabet:\n");
  proc.printAlphabet();
  //printf("State\n");
  //proc.printStates();
  std::vector<std::string> a = proc.getSensitivityList();
  //for (std::vector<int>::const_iterator i = a.begin(); i != a.end(); i++)
  //{
  //  std::cout << "Sensitive for: " << *i << '.' << states_text[*i-1] << "\n" ;
  //}
  

  Process proc2("Proc2", arrProcB, 3);
  proc2.addAlphabet(alphabet);
  
  communicationserver.addProcess(proc);
  communicationserver.addProcess(proc2);
  //communicationserver.printProcesses();
  a = proc2.getSensitivityList();
  //for (std::vector<int>::const_iterator i = a.begin(); i != a.end(); i++)
  //{
  //  std::cout << "Sensitive for: " << *i << '.' << states_text[*i-1] << "\n" ;
  //}
//
  return 1;
}
