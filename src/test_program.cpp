#include <test_program.hpp>
#include <darwin_connection.hpp>
#include <sys/time.h>

int fd = -1;

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
	packet.build();
	if (connection.transferPacket(packet))
	{
		std::cout << "SUCCES" << std::endl;
		packet = Packet(200, Packet::WRITEW, 26, (int)((((0 & 0xFF) >> 3) << 10) | (((128 & 0xFF) >> 3) << 5) | ((255 & 0xFF) >> 3)));
		packet.build();
		connection.transferPacket(packet);

		sleepCustom(300);
	}

	packet = Packet(1, Packet::WRITEW, 24, 0);
	packet.build();
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(3, Packet::WRITEW, 24, 0);
	packet.build();
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(5, Packet::WRITEW, 24, 0);
	packet.build();
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	packet = Packet(2, Packet::WRITE, 28, static_cast<unsigned char>(8));
	packet.build();
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(4, Packet::WRITE, 28, static_cast<unsigned char>(8));
	packet.build();
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;
	packet = Packet(6, Packet::WRITE, 28, static_cast<unsigned char>(8));
	packet.build();
	if (connection.transferPacket(packet))
		std::cout << "SUCCES" << std::endl;

	while (1)
	{
		printf("\r");

		printf(" ID[%d]:", 1);
		packet = Packet(1, Packet::READW, 36);
		packet.build();
		if (connection.transferPacket(packet))
		{
			int value = (int)(((int)packet.getRxPacket()[5] << 8) + (int)packet.getRxPacket()[6]);

			printf("%4d", value);
			packet = Packet(2, Packet::WRITEW, 30, 4096 - value);
			packet.build();
			connection.transferPacket(packet);
		}
		else
			printf("----");

		printf(" ID[%d]:", 3);
		packet = Packet(3, Packet::READW, 36);
		packet.build();
		if (connection.transferPacket(packet))
		{
			int value = (int)(((int)packet.getRxPacket()[5] << 8) + (int)packet.getRxPacket()[6]);

			printf("%4d", value);
			packet = Packet(4, Packet::WRITEW, 30, 4096 - value);
			packet.build();
			connection.transferPacket(packet);
		}
		else
			printf("----");

		printf(" ID[%d]:", 5);
		packet = Packet(5, Packet::READW, 36);
		packet.build();
		if (connection.transferPacket(packet))
		{
			int value = (int)(((int)packet.getRxPacket()[5] << 8) + (int)packet.getRxPacket()[6]);
			printf("%4d", value);
			packet = Packet(6, Packet::WRITEW, 30, 4096 - value);
			packet.build();
			connection.transferPacket(packet);
		}
		else
			printf("----");

		packet = Packet(200, Packet::READW, 26);
		packet.build();
		if (connection.transferPacket(packet))

		{
			int value = (int)(((int)packet.getRxPacket()[5] << 8) + (int)packet.getRxPacket()[6]);

			if (value == 0x7FFF)
				value = 0;
			else
				value++;

			packet = Packet(200, Packet::WRITEW, 26, value);
			packet.build();
			connection.transferPacket(packet);
		}

		packet = Packet(200, Packet::READW, 28);
		packet.build();
		if (connection.transferPacket(packet))

		{
			int value = (int)(((int)packet.getRxPacket()[5] << 8) + (int)packet.getRxPacket()[6]);

			if (value == 0)
				value = 0x7FFF;
			else
				value--;

			packet = Packet(200, Packet::WRITEW, 28, value);
			packet.build();
			connection.transferPacket(packet);
		}

		usleep(50000);
	}

	connection.closeConnection();
}

int not_main()
{
	struct termios newtio;
	struct serial_struct serinfo;

	std::string portname = "/dev/ttyUSB0";
	double baudrate = 1000000.0;

	fd = open(portname.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
	{
		if (fd < 0)
		{
			std::cout << "Failed" << std::endl;
			return -1;
		}
	}

	memset(&newtio, 0, sizeof(newtio));
	newtio.c_cflag = B38400 | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcsetattr(fd, TCSANOW, &newtio);

	ioctl(fd, TIOCGSERIAL, &serinfo);
	serinfo.flags &= ~ASYNC_SPD_MASK;
	serinfo.flags |= ASYNC_SPD_CUST;
	serinfo.custom_divisor = serinfo.baud_base / baudrate;
	ioctl(fd, TIOCSSERIAL, &serinfo);

	tcflush(fd, TCIFLUSH);

	WB(200, 24, 1);

	if (fd >= 0)
	{
		close(fd);
	}

	return 0;
}

int WB(unsigned char id, unsigned char address, unsigned char value)
{
	unsigned char txpacket[MAX_TX + 10] = {
			0,
	};
	unsigned char rxpacket[MAX_RX + 10] = {
			0,
	};

	txpacket[TX_ID] = id;
	txpacket[TX_INSTRUCTION] = 3; // Write Instruction
	txpacket[TX_ADDRESS] = address;
	txpacket[TX_VALUE] = value;
	txpacket[TX_LENGTH] = 4;

	int length = txpacket[TX_LENGTH] + 4;

	txpacket[0] = 0xFF;
	txpacket[1] = 0xFF;

	tcflush(fd, TCIFLUSH);

	write(fd, txpacket, length);

	length = read(fd, &rxpacket[0], 6);

	std::cout << length << std::endl;

	return 0;
}
