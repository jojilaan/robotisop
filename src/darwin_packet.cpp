#include "darwin_packet.hpp"

Packet::Packet(unsigned char id, instruction inst, unsigned char address)
{
	_id = id;
	_inst = inst;
	_address = address;
}

Packet::Packet(unsigned char id, instruction inst, unsigned char address, int value)
{
	_id = id;
	_inst = inst;
	_address = address;
	_value = static_cast<unsigned char>(value & 0xff);
	_value2 = static_cast<unsigned char>((value & 0xff00) >> 8);
}

Packet::~Packet()
{
}

void Packet::build()
{
	_txpacket[0] = 0xFF;
	_txpacket[1] = 0xFF;
	_txpacket[2] = _id;
	_txpacket[5] = _address;
	switch (_inst)
	{
	case Packet::READ:
		_txpacket[3] = 4;
		_txpacket[4] = _inst;
		_txpacket[6] = 1;
		break;
	case Packet::WRITE:
		_txpacket[3] = 4;
		_txpacket[4] = _inst;
		_txpacket[6] = _value;
		break;
	case Packet::READW:
		_txpacket[3] = 4;
		_txpacket[4] = _inst - 2;
		_txpacket[6] = 2;
		break;
	case Packet::WRITEW:
		_txpacket[3] = 5;
		_txpacket[4] = _inst - 2;
		_txpacket[6] = _value;
		_txpacket[7] = _value2;
		break;
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

unsigned char Packet::calculateChecksum(unsigned char *p)
{
	unsigned char checksum = 0x00;
	for (int i = 2; i < p[3] + 3; i++)
		checksum += p[i];
	return (~checksum);
}
