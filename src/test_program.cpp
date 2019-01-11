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
		std::cout << "moveServo(" << id << ", " << value << ") SUCCES" << std::endl;
		return true;
	}
	else
	{
		std::cout << "moveServo(" << id << ", " << value << ") FAILED" << std::endl;
		return false;
	}
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

	packet = Packet(ID_R_SHOULDER_PITCH, Packet::READW, P_PRESENT_POSITION_L);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_PITCH: " << packet.getValue() << std::endl;
	packet = Packet(ID_R_SHOULDER_ROLL, Packet::READW, P_PRESENT_POSITION_L);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_ROLL: " << packet.getValue() << std::endl;
	packet = Packet(ID_R_ELBOW, Packet::READW, P_PRESENT_POSITION_L);
	if (connection.transferPacket(packet))
		std::cout << "R_ELBOW: " << packet.getValue() << std::endl;

	packet = Packet(ID_L_SHOULDER_PITCH, Packet::READW, P_PRESENT_POSITION_L);
	if (connection.transferPacket(packet))
		std::cout << "L_SHOULDER_PITCH: " << packet.getValue() << std::endl;
	packet = Packet(ID_L_SHOULDER_ROLL, Packet::READW, P_PRESENT_POSITION_L);
	if (connection.transferPacket(packet))
		std::cout << "L_SHOULDER_ROLL: " << packet.getValue() << std::endl;
	packet = Packet(ID_L_ELBOW, Packet::READW, P_PRESENT_POSITION_L);
	if (connection.transferPacket(packet))
		std::cout << "L_ELBOW: " << packet.getValue() << std::endl;

	usleep(50000);

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

	usleep(50000);

	connection.closeConnection();

	return 0;
}
