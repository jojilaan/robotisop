#include "darwin_connection.hpp"

Connection::Connection(std::string portname)
{
	_portname = portname;
	_fd = -1;
}

Connection::~Connection()
{
}

// Creates a new connection to the given port.
bool Connection::openConnection()
{
	// Prevents leaving the current filedescriptor unclosed if open.
	if (_fd >= 0)
	{
		closeConnection();
	}

	_fd = open(_portname.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (_fd < 0)
	{
		if (debug)
			std::cout << "openConnection() failed with the following error: " << strerror(errno) << std::endl;
		return false;
	}
	else
	{
		if (debug)
			std::cout << "openConnection() success" << std::endl;
		return true;
	}
}

// Closes the current connection to the given port if opened.
bool Connection::closeConnection()
{
	if (close(_fd) < 0)
	{
		if (debug)
			std::cout << "closeConnection() failed with the following error: " << strerror(errno) << std::endl;
		return false;
	}
	else
	{
		if (debug)
			std::cout << "closeConnection() success" << std::endl;
		return true;
	}
}

// Transfers a packet across the connection
bool transferPacket(Packet packet)
{
	return true;
}
