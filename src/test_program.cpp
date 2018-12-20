#include <termios.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
  struct termios newio;
  struct serial_struct serinfo;

  std::string portname = "/dev/ttyUSB0";
  double baudrate = 1000000.0;

  int fd = -1;
  
  fd = open(portname.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
  {
    if (fd < 0) {
      std::cout << "FAILED" << std::endl;
    } else {
      std::cout << "Succes" << std::endl;
    }
  }

  if (fd >= 0) {
    close(fd);
  }

  return 0;
}