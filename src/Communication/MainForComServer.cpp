#include <iostream>
#include <thread>
#include "ProcesA.hpp"

using namespace std;


int main()
{

  ProcesA a;

  a.GetData();
  cout<<"HEY, you, I'm alive! Oh, and Hello World!\n";
  cin.get();

  return 1;
}
