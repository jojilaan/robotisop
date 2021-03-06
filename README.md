# Robotis OP2 implementation using the RT-Linux kernel on Ubuntu/Lubuntu 16.04

Before starting the code, make sure that your baud rate is set to the correct parameters. To set the correct flags and parameters install `setserial`

```bash
sudo apt-get install setserial
```

After installing `setserial` check the parameters set for `ttyUSB0` by using the following command:

```bash
sudo setserial -g -a /dev/ttyUSB0
/dev/ttyUSB0, Line 0, UART: unknown, Port: 0x0000, IRQ: 0
    Baud_base: 24000000, close_delay: 0, divisor: 1
    closing_wait: infinite
    Flags: spd_normal
```

Use the following commands to change the flags and divisor to set te correct baud rate for the CM-730.

```bash
sudo setserial /dev/ttyUSB0 divisor 24
sudo setserial /dev/ttyUSB0 spd_cust
sudo setserial /dev/ttyUSB0 low_latency
```

And check again if the parameters are set correctly:

```bash
sudo setserial -g -a /dev/ttyUSB0
/dev/ttyUSB0, Line 0, UART: unknown, Port: 0x0000, IRQ: 0
    Baud_base: 24000000, close_delay:0, divisor: 24
    closing_wait: infinite
    Flags: spd_cust low_latency
```

Change these parameters everytime you reboot your system, to make the connection with the CM-730.
