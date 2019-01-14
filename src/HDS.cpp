#include <HDS.hpp>

HDS::HDS(std::string portname)
{
	_connection = Connection(portname);
	_connection.openConnection();
}

HDS::~HDS()
{
	_connection.closeConnection();
}

bool HDS::dxlPowerOn()
{
	Packet packet = Packet(ID_CM, Packet::WRITE, P_DXL_POWER, static_cast<unsigned char>(1));
	if (_connection.transferPacket(packet))
	{
		if (debug)
			std::cout << "dxlPowerOn() succes" << std::endl;
		packet = Packet(ID_CM, Packet::WRITEW, P_LED_HEAD_L, (int)((((0 & 0xFF) >> 3) << 10) | (((128 & 0xFF) >> 3) << 5) | ((255 & 0xFF) >> 3)));
		_connection.transferPacket(packet);

		usleep(300000);
		return true;
	}
	else
	{
		if (debug)
			std::cout << "dxlPowerOn() failed" << std::endl;
		_connection.closeConnection();

		return false;
	}
}

bool HDS::moveServo(unsigned char id, int value)
{
	Packet packet = Packet(id, Packet::WRITEW, P_GOAL_POSITION_L, value);
	if (_connection.transferPacket(packet))
	{
		if (debug)
			std::cout << "moveServo(" << static_cast<int>(id) << ", " << value << ") SUCCES" << std::endl;
		return true;
	}
	else
	{
		if (debug)
			std::cout << "moveServo(" << static_cast<int>(id) << ", " << value << ") FAILED" << std::endl;
		return false;
	}
}

int HDS::readServo(unsigned char id)
{
	Packet packet = Packet(id, Packet::READW, P_PRESENT_POSITION_L);
	if (_connection.transferPacket(packet))
	{
		if (debug)
			std::cout << "readServo(" << static_cast<int>(id) << " => " << packet.getValue() << " SUCCES" << std::endl;
		return packet.getValue();
	}
	else
	{
		if (debug)
			std::cout << "readServo(" << static_cast<int>(id) << " FAILED" << std::endl;
		return -1;
	}
}

bool HDS::readMoveServo(unsigned char id)
{
	int value = readServo(id);

	if (value < 0)
	{
		return false;
	}

	moveServo(id, value);
	return true;
}

void HDS::init()
{
	dxlPowerOn();

	usleep(1000000);

	std::cout << "set P_GAIN" << std::endl;

	Packet packet = Packet(ID_R_SHOULDER_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_SHOULDER_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_ELBOW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_SHOULDER_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_SHOULDER_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_ELBOW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_HIP_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_HIP_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_HIP_YAW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_KNEE, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_ANKLE_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_ANKLE_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_HIP_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_HIP_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_HIP_YAW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_KNEE, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_ANKLE_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_ANKLE_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (_connection.transferPacket(packet) && debug)
		std::cout << "SUCCES" << std::endl;

	std::cout << "lock legs" << std::endl;

	readMoveServo(ID_R_HIP_PITCH);
	readMoveServo(ID_R_HIP_ROLL);
	readMoveServo(ID_R_HIP_YAW);
	readMoveServo(ID_R_KNEE);
	readMoveServo(ID_R_ANKLE_PITCH);
	readMoveServo(ID_R_ANKLE_ROLL);
	readMoveServo(ID_L_HIP_PITCH);
	readMoveServo(ID_L_HIP_ROLL);
	readMoveServo(ID_L_HIP_YAW);
	readMoveServo(ID_L_KNEE);
	readMoveServo(ID_L_ANKLE_PITCH);
	readMoveServo(ID_L_ANKLE_ROLL);

	std::cout << "" << readServo(ID_R_SHOULDER_PITCH) << std::endl;
	std::cout << "" << readServo(ID_L_SHOULDER_PITCH) << std::endl;
	std::cout << "" << readServo(ID_R_SHOULDER_ROLL) << std::endl;
	std::cout << "" << readServo(ID_L_SHOULDER_ROLL) << std::endl;
	std::cout << "" << readServo(ID_R_ELBOW) << std::endl;
	std::cout << "" << readServo(ID_L_ELBOW) << std::endl;

}

void HDS::beginPosition()
{
	std::cout << "beginPosition()" << std::endl;

	usleep(1000000);

	moveServo(ID_R_SHOULDER_PITCH, 1948);
	moveServo(ID_R_SHOULDER_ROLL, 1560);
	moveServo(ID_R_ELBOW, 980);
	moveServo(ID_L_SHOULDER_PITCH, 2127);
	moveServo(ID_L_SHOULDER_ROLL, 2534);
	moveServo(ID_L_ELBOW, 3107);
}

	void HDS::rShoulderRollOut() {}
	void HDS::lShoulderRollOut() {}
	void HDS::rShoulderRollIn() {}
	void HDS::lShoulderRollIn() {}
	void HDS::rShoulderTurnIn() {}
	void HDS::lShoulderTurnIn() {}
	void HDS::rShoulderTurnOut() {}
	void HDS::lShoulderTurnOut() {}
	void HDS::rElbowOut() {}
	void HDS::lElbowOut() {}
	void HDS::rElbowIn() {}
	void HDS::lElbowIn() {}

void HDS::makeTransition(std::string trans)
{

}
