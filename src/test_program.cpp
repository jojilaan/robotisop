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
	Packet packet = Packet(200, Packet::WRITE, 24, static_cast<unsigned char>(1));
	if (connection.transferPacket(packet))
	{
		std::cout << "SUCCES" << std::endl;
		packet = Packet(200, Packet::WRITEW, 26, (int)((((0 & 0xFF) >> 3) << 10) | (((128 & 0xFF) >> 3) << 5) | ((255 & 0xFF) >> 3)));
		connection.transferPacket(packet);

		sleepCustom(300);
	}

	packet = Packet(1, Packet::WRITEW, 24, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(3, Packet::WRITEW, 24, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(5, Packet::WRITEW, 24, 0);
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	packet = Packet(2, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(4, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(6, Packet::WRITE, 28, static_cast<unsigned char>(8));
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	while (1)
	{
		packet = Packet(1, Packet::READW, 36);
		if (connection.transferPacket(packet))
		{
			int value = (int)(((int)packet.getRxPacket()[6] << 8) + (int)packet.getRxPacket()[5]);
			packet = Packet(2, Packet::WRITEW, 30, 4096 - value);
			connection.transferPacket(packet);
		}

		packet = Packet(3, Packet::READW, 36);
		if (connection.transferPacket(packet))
		{
			int value = (int)(((int)packet.getRxPacket()[6] << 8) + (int)packet.getRxPacket()[5]);
			packet = Packet(4, Packet::WRITEW, 30, 4096 - value);
			connection.transferPacket(packet);
		}

		packet = Packet(5, Packet::READW, 36);
		if (connection.transferPacket(packet))
		{
			int value = (int)(((int)packet.getRxPacket()[6] << 8) + (int)packet.getRxPacket()[5]);
			packet = Packet(6, Packet::WRITEW, 30, 4096 - value);
			connection.transferPacket(packet);
		}

		usleep(50000);
	}

	connection.closeConnection();
}
