#include "darwin_packet.hpp"

Packet::Packet(unsigned char id, instruction inst, unsigned char address, unsigned char value)
{
	_id = id;
	_inst = inst;
	_address = address;
	_value = value;
	_value2 = 0;
	_length = 4;
}

Packet::Packet(unsigned char id, instruction inst, unsigned char address, int value)
{
	_id = id;
	_inst = inst;
	_address = address;
	_value = static_cast<unsigned char>(value & 0xff);
	_value2 = static_cast<unsigned char>((value & 0xff00) >> 8);
	_length = 5;
}

Packet::~Packet()
{
}

void Packet::build()
{
	_txpacket[0] = 0xFF;
	_txpacket[1] = 0xFF;
	_txpacket[2] = _id;
	_txpacket[3] = _length;
	_txpacket[4] = _inst;
	_txpacket[5] = _address;
	if (_inst == Packet::READ)
	{
		_txpacket[6] = 1;
	}
	else
	{
		_txpacket[6] = _value;
		if (_value2 != 0)
			_txpacket[7] = _value2;
	}
}

unsigned char *Packet::getTxPacket()
{
	return _txpacket;
}

unsigned char *Packet::getRxPacket()
{
	return _rxpacket;
}

unsigned char Packet::calculateChecksum(unsigned char* p)
{
	unsigned char checksum = 0x00;
	for(int i = 2; i < p[3] + 3; i++ )
		checksum += p[i];
	return (~checksum);
}
