#ifndef _DARWIN_PACKET_HPP_
#define _DARWIN_PACKET_HPP_

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

	void build();
	unsigned char *getTxPacket();
	unsigned char *getRxPacket();
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
};

#endif
