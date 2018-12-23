#ifndef _DARWIN_PACKET_HPP_
#define _DARWIN_PACKET_HPP_

#include "darwin_debug.hpp"

class Packet {
public:
	enum instruction {
		PING = 1,
		READ,
		WRITE
	};

	Packet(unsigned char id, instruction inst, unsigned char address, unsigned char value);
	~Packet();

	bool build();
	unsigned char* getTxPacket();
	unsigned char* getRxPacket();

private:
	unsigned char _txpacket[256 + 10];
	unsigned char _rxpacket[1024 + 10];
	unsigned char _id;
	instruction _inst;
	unsigned char _address;
	unsigned char _value;
	unsigned char _length;
};

#endif
