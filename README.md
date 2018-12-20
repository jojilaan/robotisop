# Robotis OP2 implementation using the RT-Linux kernel on Ubuntu/Lubuntu 16.04

Before starting the code, make sure that your baud rate is set to the correct parameters. To set the correct flags and parameters install `setserial`

```bash
sudo apt-get install setserial
```

After installing `setserial` check the parameters set for `ttyUSB0` by using the following command:

```bash
sudo setserial -g -a /dev/ttyUSB0
/dev/ttyUSB0, Line 0, UART: unknown, Port: 0x0000, IRQL0
	Baud_base: 24000000, close_delay:0, divisor: 1
	closing_wait: infinite
	Flags: spd_normal
```
