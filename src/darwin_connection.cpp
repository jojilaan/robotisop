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
			std::cout << "openConnection(" << _portname << ") failed with the following error: " << strerror(errno) << std::endl;

		return false;
	}

	if (!initConnection())
	{
		closeConnection();
		if (debug)
			std::cout << "openConnection(" << _portname << ") failed" << std::endl;

		return false;
	};

	if (debug)
		std::cout << "openConnection(" << _portname << ") success" << std::endl;

	return true;
}

// Closes the current connection to the given port if opened.
bool Connection::closeConnection()
{
	if (close(_fd) < 0)
	{
		if (debug)
			std::cout << "closeConnection(" << _fd << ") failed with the following error: " << strerror(errno) << std::endl;

		return false;
	}
	else
	{
		if (debug)
			std::cout << "closeConnection(" << _fd << ") success" << std::endl;

		return true;
	}
}

bool Connection::initConnection()
{
	struct termios termios_p;
	struct serial_struct serial_struct_p;

	memset(&termios_p, 0, sizeof(termios_p));

	/* Control modes:
	 * Baud speed mask (4+1 bits) of 38400.
	 * Character size mask of 8.
	 * Ignore modem control lines.
	 * Enable receiver.
	 */
	termios_p.c_cflag = B38400 | CS8 | CLOCAL | CREAD;
	/* Input modes:
	 * Ignore framing errors and parity errors.
	 */
	termios_p.c_iflag = IGNPAR;
	/* Output modes:
	 */
	termios_p.c_oflag = 0;
	/* Local modes:
	 */
	termios_p.c_lflag = 0;
	/* Special characters:
	 * Timeout in deciseconds for noncanonical read (TIME).
	 * Minimum number of characters for noncanonical read (MIN).
	 *
	 * MIN == 0; TIME == 0:
	 * If data is available, read returns immediately,
	 * with the lesser of the number of bytes available,
	 * or the number of bytes requested.
	 * If no data is available, read returns 0.
	 */
	termios_p.c_cc[VTIME] = 0;
	termios_p.c_cc[VMIN] = 0;

	/* Note that tcsetattr() returns success if any of the requested changes could be successfully carried out.
	 * Therefore, when making multiple changes it may be necessary to follow this call with a
	 * further call to tcgetattr() to check that all changes have been performed successfully.
	 *
	 * TCSANOW: The change occurs immediately.
	 */
	if (tcsetattr(_fd, TCSANOW, &termios_p) < 0 && debug)
		std::cout << "tcsetattr() failed" << std::endl;

	if (ioctl(_fd, TIOCGSERIAL, &serial_struct_p) < 0)
	{
		if (debug)
			std::cout << "initConnection(" << _fd << ") failed with the following error: " << strerror(errno) << std::endl;

		return false;
	}

	serial_struct_p.flags &= ~ASYNC_SPD_MASK;
	serial_struct_p.flags |= ASYNC_SPD_CUST;
	serial_struct_p.custom_divisor = serial_struct_p.baud_base / 1000000.0;

	if (ioctl(_fd, TIOCSSERIAL, &serial_struct_p) < 0)
	{
		if (debug)
			std::cout << "initConnection(" << _fd << ") failed with the following error: " << strerror(errno) << std::endl;

		return false;
	}

	if (tcflush(_fd, TCIFLUSH) < 0 && debug)
		std::cout << "tcflush() failed" << std::endl;

	// m_ByteTransferTime = (1000.0 / baudrate) * 12.0;

	if (debug)
		std::cout << "initConnection(" << _fd << ") success" << std::endl;

	return true;
}

// Transfers a packet across the connection
bool transferPacket(Packet packet)
{
	return true;
}
