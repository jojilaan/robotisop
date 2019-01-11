#include <test_program.hpp>
#include <darwin_connection.hpp>

double getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return ((double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0);
}

void sleepCustom(double msec)
{
	double start_time = getCurrentTime();
	double curr_time = start_time;

	do
	{
		usleep((start_time + msec) - curr_time);
		curr_time = getCurrentTime();
	} while (curr_time - start_time < msec);
}

bool moveServo(Connection &connection, unsigned char id, int value)
{
	Packet packet = Packet(id, Packet::WRITEW, P_GOAL_POSITION_L, value);
	if (connection.transferPacket(packet))
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

int readServo(Connection &connection, unsigned char id)
{
	Packet packet = Packet(id, Packet::READW, P_PRESENT_POSITION_L);
	if (connection.transferPacket(packet))
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

bool readMoveServo(Connection &connection, unsigned char id)
{
	int value = readServo(connection, id);

	if (value < 0)
	{
		return false;
	}

	moveServo(connection, id, value);
	return true;
}

int main()
{
	Connection connection = Connection("/dev/ttyUSB0");
	connection.openConnection();
	Packet packet = Packet(ID_CM, Packet::WRITE, P_DXL_POWER, static_cast<unsigned char>(1));
	if (connection.transferPacket(packet))
	{
		std::cout << "SUCCES" << std::endl;
		packet = Packet(ID_CM, Packet::WRITEW, P_LED_HEAD_L, (int)((((0 & 0xFF) >> 3) << 10) | (((128 & 0xFF) >> 3) << 5) | ((255 & 0xFF) >> 3)));
		connection.transferPacket(packet);

		sleepCustom(300);
	}
	else
	{
		std::cout << "DXL Power on failed" << std::endl;
		connection.closeConnection();
		return -1;
	}

	packet = Packet(ID_R_SHOULDER_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_SHOULDER_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_ELBOW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_SHOULDER_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_SHOULDER_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_ELBOW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	packet = Packet(ID_R_HIP_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_HIP_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_HIP_YAW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_KNEE, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_ANKLE_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_ANKLE_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_HIP_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_HIP_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_HIP_YAW, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_KNEE, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_ANKLE_PITCH, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_ANKLE_ROLL, Packet::WRITE, P_P_GAIN, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	readServo(connection, ID_R_SHOULDER_PITCH);
	readServo(connection, ID_R_SHOULDER_ROLL);
	readServo(connection, ID_R_ELBOW);
	readServo(connection, ID_L_SHOULDER_PITCH);
	readServo(connection, ID_L_SHOULDER_ROLL);
	readServo(connection, ID_L_ELBOW);

	readMoveServo(connection, ID_R_HIP_PITCH);
	readMoveServo(connection, ID_R_HIP_ROLL);
	readMoveServo(connection, ID_R_HIP_YAW);
	readMoveServo(connection, ID_R_KNEE);
	readMoveServo(connection, ID_R_ANKLE_PITCH);
	readMoveServo(connection, ID_R_ANKLE_ROLL);
	readMoveServo(connection, ID_L_HIP_PITCH);
	readMoveServo(connection, ID_L_HIP_ROLL);
	readMoveServo(connection, ID_L_HIP_YAW);
	readMoveServo(connection, ID_L_KNEE);
	readMoveServo(connection, ID_L_ANKLE_PITCH);
	readMoveServo(connection, ID_L_ANKLE_ROLL);

	usleep(1000000);

	// Right arm init
	moveServo(connection, ID_R_SHOULDER_PITCH, 1948);
	moveServo(connection, ID_R_SHOULDER_ROLL, 1560);
	moveServo(connection, ID_R_ELBOW, 980);

	// Left arm init
	moveServo(connection, ID_L_SHOULDER_PITCH, 2127);
	moveServo(connection, ID_L_SHOULDER_ROLL, 2534);
	moveServo(connection, ID_L_ELBOW, 3107);

	usleep(1000000);

	// First position
	moveServo(connection, ID_R_SHOULDER_PITCH, 3451);
	moveServo(connection, ID_L_SHOULDER_PITCH, 625);

	usleep(1000000);

	// Second position
	moveServo(connection, ID_R_ELBOW, 1480);
	moveServo(connection, ID_L_ELBOW, 2621);

	for (size_t i = 0; i < 5; i++)
	{
		usleep(500000);

		// Clap
		moveServo(connection, ID_R_SHOULDER_ROLL, 1240);
		moveServo(connection, ID_L_SHOULDER_ROLL, 2850);

		usleep(500000);

		moveServo(connection, ID_R_SHOULDER_ROLL, 1560);
		moveServo(connection, ID_L_SHOULDER_ROLL, 2534);
	}

	usleep(500000);

	packet = Packet(ID_R_SHOULDER_PITCH, Packet::WRITEW, P_TORQUE_ENABLE, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_SHOULDER_ROLL, Packet::WRITEW, P_TORQUE_ENABLE, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_R_ELBOW, Packet::WRITEW, P_TORQUE_ENABLE, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_SHOULDER_PITCH, Packet::WRITEW, P_TORQUE_ENABLE, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_SHOULDER_ROLL, Packet::WRITEW, P_TORQUE_ENABLE, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(ID_L_ELBOW, Packet::WRITEW, P_TORQUE_ENABLE, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	connection.closeConnection();

	return 0;
}
