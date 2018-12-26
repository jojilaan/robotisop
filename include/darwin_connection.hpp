#ifndef _DARWIN_CONNECTION_HPP_
#define _DARWIN_CONNECTION_HPP_

#include "darwin_debug.hpp"
#include "darwin_packet.hpp"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>

class Connection {
public:
	Connection(std::string portname);
	~Connection();

	bool openConnection();
	bool closeConnection();

	bool transferPacket(Packet packet);

private:
	std::string _portname;
	int _fd;
};

#endif
