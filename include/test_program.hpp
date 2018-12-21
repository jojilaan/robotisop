#ifndef _TEST_PROGRAM_HPP_
#define _TEST_PROGRAM_HPP_

#include <termios.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

#define MAX_TX 256
#define MAX_RX 1024

#define TX_ID 2
#define TX_INSTRUCTION 4
#define TX_ADDRESS 5
#define TX_VALUE 6
#define TX_LENGTH 3

// WriteByte
int WB(unsigned char id, unsigned char address, unsigned char value);

#endif
