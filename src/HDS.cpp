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

void HDS::readArms()
{
	dxlPowerOn();
	std::cout << "ID_R_SHOULDER_PITCH: " << readServo(ID_R_SHOULDER_PITCH) << std::endl;
	std::cout << "ID_L_SHOULDER_PITCH: " << readServo(ID_L_SHOULDER_PITCH) << std::endl;
	std::cout << "ID_R_SHOULDER_ROLL: " << readServo(ID_R_SHOULDER_ROLL) << std::endl;
	std::cout << "ID_L_SHOULDER_ROLL: " << readServo(ID_L_SHOULDER_ROLL) << std::endl;
	std::cout << "ID_R_ELBOW: " << readServo(ID_R_ELBOW) << std::endl;
	std::cout << "ID_L_ELBOW: " << readServo(ID_L_ELBOW) << std::endl;
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

void HDS::rShoulderRollOut()
{
	moveServo(ID_R_SHOULDER_ROLL, 2562);
	do
	{
	} while (abs(readServo(ID_R_SHOULDER_ROLL) - 2562) <= 10);
}
void HDS::rShoulderRollIn()
{
	moveServo(ID_R_SHOULDER_ROLL, 1560);
	do
	{
	} while (abs(readServo(ID_R_SHOULDER_ROLL) - 1560) <= 10);
}
void HDS::rShoulderTurnOut()
{
	moveServo(ID_R_SHOULDER_PITCH, 963);
	do
	{
	} while (abs(readServo(ID_R_SHOULDER_PITCH) - 963) <= 10);
}
void HDS::rShoulderTurnIn()
{
	moveServo(ID_R_SHOULDER_PITCH, 1948);
	do
	{
	} while (abs(readServo(ID_R_SHOULDER_PITCH) - 1948) <= 10);
}
void HDS::rElbowOut()
{
	moveServo(ID_R_ELBOW, 2043);
	do
	{
	} while (abs(readServo(ID_R_ELBOW) - 2043) <= 10);
}
void HDS::rElbowIn()
{
	moveServo(ID_R_ELBOW, 980);
	do
	{
	} while (abs(readServo(ID_R_ELBOW) - 980) <= 10);
}
void HDS::lShoulderRollOut()
{
	moveServo(ID_L_SHOULDER_ROLL, 1520);
	do
	{
	} while (abs(readServo(ID_L_SHOULDER_ROLL) - 1520) <= 10);
}
void HDS::lShoulderRollIn()
{
	moveServo(ID_L_SHOULDER_ROLL, 2534);
	do
	{
	} while (abs(readServo(ID_L_SHOULDER_ROLL) - 2534) <= 10);
}
void HDS::lShoulderTurnOut()
{
	moveServo(ID_L_SHOULDER_PITCH, 1067);
	do
	{
	} while (abs(readServo(ID_L_SHOULDER_PITCH) - 1067) <= 10);
}
void HDS::lShoulderTurnIn()
{
	moveServo(ID_L_SHOULDER_PITCH, 2127);
	do
	{
	} while (abs(readServo(ID_L_SHOULDER_PITCH) - 2127) <= 10);
}
void HDS::lElbowOut()
{
	moveServo(ID_L_ELBOW, 2063);
	do
	{
	} while (abs(readServo(ID_L_ELBOW) - 2063) <= 10);
}
void HDS::lElbowIn()
{
	moveServo(ID_L_ELBOW, 3107);
	do
	{
	} while (abs(readServo(ID_L_ELBOW) - 3107) <= 10);
}

void HDS::makeTransition(std::string trans)
{
	if (trans == "left.ShoulderRInPosition")
	{
		lShoulderRollOut();
	}
	else if (trans == "left.ShoulderROutPosition")
	{
		lShoulderRollIn();
	}
	else if (trans == "left.ShoulderPInPosition")
	{
		lShoulderTurnOut();
	}
	else if (trans == "left.ShoulderPOutPosition")
	{
		lShoulderTurnIn();
	}
	else if (trans == "left.ElbowInPosition")
	{
		lElbowOut();
	}
	else if (trans == "left.ElbowOutPosition")
	{
		lElbowIn();
	}
	else if (trans == "right.ShoulderRInPosition")
	{
		rShoulderRollOut();
	}
	else if (trans == "right.ShoulderROutPosition")
	{
		rShoulderRollIn();
	}
	else if (trans == "right.ShoulderPInPosition")
	{
		rShoulderTurnOut();
	}
	else if (trans == "right.ShoulderPOutPosition")
	{
		rShoulderTurnIn();
	}
	else if (trans == "right.ElbowInPosition")
	{
		rElbowOut();
	}
	else if (trans == "right.ElbowOutPosition")
	{
		rElbowIn();
	}
}
