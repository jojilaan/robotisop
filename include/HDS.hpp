#ifndef _HDS_HPP_
#define _HDS_HPP_

#include <Process.hpp>
#include <darwin_connection.hpp>

class HDS
{
public:
	Connection _connection;

	HDS(std::string portname);
	~HDS();
	void init();
	void beginPosition();
	void shouldersUp();
	void shouldersDown();
	void shouldersInward();
	void shouldersOutward();
	void elbowsUp();
	void elbowsDown();

private:
	bool moveServo(unsigned char id, int value);
	int readServo(unsigned char id);
	bool readMoveServo(unsigned char id);
	bool dxlPowerOn();
};

#endif
