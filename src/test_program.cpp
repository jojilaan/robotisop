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

	packet = Packet(ID_R_SHOULDER_PITCH, Packet::WRITEW, P_GOAL_POSITION_L, 1948);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_PITCH: SUCCES" << std::endl;
	packet = Packet(ID_R_SHOULDER_ROLL, Packet::WRITEW, P_GOAL_POSITION_L, 1537);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_ROLL: SUCCES" << std::endl;
	packet = Packet(ID_R_ELBOW, Packet::WRITEW, P_GOAL_POSITION_L, 1195);
	if (connection.transferPacket(packet))
		std::cout << "R_ELBOW: SUCCES" << std::endl;

	packet = Packet(ID_L_SHOULDER_PITCH, Packet::WRITEW, P_GOAL_POSITION_L, 2127);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_PITCH: SUCCES" << std::endl;
	packet = Packet(ID_L_SHOULDER_ROLL, Packet::WRITEW, P_GOAL_POSITION_L, 2534);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_ROLL: SUCCES" << std::endl;
	packet = Packet(ID_L_ELBOW, Packet::WRITEW, P_GOAL_POSITION_L, 3107);
	if (connection.transferPacket(packet))
		std::cout << "R_ELBOW: SUCCES" << std::endl;

	usleep(50000);

	packet = Packet(ID_R_SHOULDER_PITCH, Packet::WRITEW, P_GOAL_POSITION_L, 3451);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_PITCH: SUCCES" << std::endl;
	// packet = Packet(ID_R_SHOULDER_ROLL, Packet::WRITEW, P_GOAL_POSITION_L, 1537);
	// if (connection.transferPacket(packet))
	// 	std::cout << "R_SHOULDER_ROLL: SUCCES" << std::endl;
	// packet = Packet(ID_R_ELBOW, Packet::WRITEW, P_GOAL_POSITION_L, 1195);
	// if (connection.transferPacket(packet))
	// 	std::cout << "R_ELBOW: SUCCES" << std::endl;

	packet = Packet(ID_L_SHOULDER_PITCH, Packet::WRITEW, P_GOAL_POSITION_L, 625);
	if (connection.transferPacket(packet))
		std::cout << "R_SHOULDER_PITCH: SUCCES" << std::endl;
	// packet = Packet(ID_L_SHOULDER_ROLL, Packet::WRITEW, P_GOAL_POSITION_L, 2534);
	// if (connection.transferPacket(packet))
	// 	std::cout << "R_SHOULDER_ROLL: SUCCES" << std::endl;
	// packet = Packet(ID_L_ELBOW, Packet::WRITEW, P_GOAL_POSITION_L, 3107);
	// if (connection.transferPacket(packet))
	// 	std::cout << "R_ELBOW: SUCCES" << std::endl;

	usleep(50000);

	connection.closeConnection();

	return 0;
}
