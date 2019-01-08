#ifndef _DARWIN_PACKET_HPP_
#define _DARWIN_PACKET_HPP_

#define PACKET_ID 2
#define PACKET_LENGTH 3
#define PACKET_INSTRUCTION 4
#define PACKET_ADDRESS 5
#define PACKET_VALUE 6

#include "darwin_debug.hpp"

class Packet
{
public:
	enum instruction
	{
		READ = 2,
		WRITE,
		READW,
		WRITEW,
	};

	Packet(unsigned char id, instruction inst, unsigned char address);
	Packet(unsigned char id, instruction inst, unsigned char address, int value);
	~Packet();

	unsigned char *getTxPacket();
	unsigned char *getRxPacket();
	int getValue();
	static unsigned char calculateChecksum(unsigned char *p);

private:
	unsigned char _txpacket[256 + 10] = {0, };
	unsigned char _rxpacket[1024 + 10] = {0, };
	unsigned char _id;
	instruction _inst;
	unsigned char _address;
	unsigned char _value;
	unsigned char _value2;
	unsigned char _length;

	void build();
};

#endif
