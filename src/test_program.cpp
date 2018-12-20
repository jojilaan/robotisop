#include <termios.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define MAX_TX 256
#define MAX_RX 1024

#define TX_ID 2
#define TX_INSTRUCTION 4
#define TX_ADDRESS 5
#define TX_VALUE 6
#define TX_LENGTH 3

int fd = -1;

int WB(int id, int address, int value);

int main(int argc, char **argv)
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

int WB(unsigned int id, unsigned int address, unsigned int value)
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

  return 0;
}