#include "Process.hpp"
#include <iostream> 

Process::Process(std::string name)
{
    _name = name; 
    //_a = communicationserver; 
	//_alphabet.push_back("wrtie");
	//_alphabet.push_back("read");
    // commincationdriver
    // fsm
    // actions
    // sesitiveActions
    //
   
}

Process::~Process()
{}

void Process::addAlphabet(std::vector<std::string> alphabet)
{
    // ADD to yourself 
    _alphabet = alphabet; 
    // Add to communicationServer; 
    //_communicationserver.addAlphabet(_alphabet); 
}

void Process::addStates(std::vector<int> states)
{
    // ADD to yourself 
    _states = states; 
}

void Process::printAlphabet()
{
    // ADD to yourself 
    for(const auto alpha : _alphabet)
    {
        std::cout << alpha; 
        //printf("%s, ", alpha);
    }
    printf("\n");
}

void Process::printStates()
{
    // ADD to yourself 
    for(const auto state : _states)
    {
        printf("%d, ", state);
    }
    printf("\n");
}

std::string Process::getName()
{
    return _name; 
}