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

	// DXL power on
	Packet packet = Packet(200, Packet::WRITE, 24, static_cast<unsigned char>(1));
	if (connection.transferPacket(packet))
	{
		std::cout << "SUCCES" << std::endl;
		packet = Packet(200, Packet::WRITEW, 26, (int)((((0 & 0xFF) >> 3) << 10) | (((128 & 0xFF) >> 3) << 5) | ((255 & 0xFF) >> 3)));
		connection.transferPacket(packet);

		sleepCustom(300);
	}

	// Left arm
	packet = Packet(2, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(4, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(6, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	// Right arm
	packet = Packet(1, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(3, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(5, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	connection.closeConnection();
	return 0;
}
