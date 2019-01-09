#include "darwin_packet.hpp"

Packet::Packet(unsigned char id, instruction inst, unsigned char address)
{
	_id = id;
	_inst = inst;
	_address = address;
	build();
}

Packet::Packet(unsigned char id, instruction inst, unsigned char address, int value)
{
	_id = id;
	_inst = inst;
	_address = address;
	_value = static_cast<unsigned char>(value & 0xff);
	_value2 = static_cast<unsigned char>((value & 0xff00) >> 8);
	build();
}

Packet::~Packet()
{
}

void Packet::build()
{
	_txpacket[0] = 0xFF;
	_txpacket[1] = 0xFF;
	_txpacket[PACKET_ID] = _id;
	_txpacket[PACKET_ADDRESS] = _address;
	switch (_inst)
	{
	case Packet::READ:
		_txpacket[PACKET_LENGTH] = 4;
		_txpacket[PACKET_INSTRUCTION] = _inst;
		_txpacket[PACKET_VALUE] = 1;
		break;
	case Packet::WRITE:
		_txpacket[PACKET_LENGTH] = 4;
		_txpacket[PACKET_INSTRUCTION] = _inst;
		_txpacket[PACKET_VALUE] = _value;
		break;
	case Packet::READW:
		_txpacket[PACKET_LENGTH] = 4;
		_txpacket[PACKET_INSTRUCTION] = _inst - 2;
		_txpacket[PACKET_VALUE] = 2;
		break;
	case Packet::WRITEW:
		_txpacket[PACKET_LENGTH] = 5;
		_txpacket[PACKET_INSTRUCTION] = _inst - 2;
		_txpacket[PACKET_VALUE] = _value;
		_txpacket[PACKET_VALUE + 1] = _value2;
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

int Packet::getValue()
{
	switch(_inst) {
		case READ:
			return (int)_rxpacket[PACKET_ADDRESS];
		case READW:
			return (int)(((int)_rxpacket[PACKET_VALUE] << 8) + (int)_rxpacket[PACKET_ADDRESS]);
		default:
			return 0;
	}
}

unsigned char Packet::calculateChecksum(unsigned char *p)
{
	unsigned char checksum = 0x00;
	for (int i = 2; i < p[3] + 3; i++)
		checksum += p[i];
	return (~checksum);
}
