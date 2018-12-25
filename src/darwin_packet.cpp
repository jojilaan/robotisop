#include "darwin_packet.hpp"

Packet::Packet(unsigned char id, instruction inst, unsigned char address, unsigned char value)
{
	_id = id;
	_inst = inst;
	_address = address;
	_value = value;
	_length = 4;
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
