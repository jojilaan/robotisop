// my_class.h
#ifndef COMMUNICATIONSERVER_H // include guard
#define COMMUNICATIONSERVER_H
#include <vector>
#include <map>

class CommunicationServer
{
	public:
	CommunicationServer();
	~CommunicationServer();

	
	std::string test; 

	private:
	std::vector<int> process;

}

#endif /* MY_CLASS_H */
