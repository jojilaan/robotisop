#include "darwin_connection.hpp"

Connection::Connection(std::string portname)
{
	_portname = portname;
	_fd = -1;
}

bool Connection::openConnection()
{
	_fd = open(_portname.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (_fd < 0)
	{
		if (debug)
			std::cout << "openConnection failed" << std::endl;
		return false;
	}
	else
	{
		if (debug)
			std::cout << "openConnection success" << std::endl;
		return true;
	}
}

bool Connection::closeConnection()
{
}

bool transferPacket(Packet packet)
{
}
