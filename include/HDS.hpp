#ifndef _HDS_HPP_
#define _HDS_HPP_

#include <darwin_connection.hpp>
#include <linux/serial.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>

#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <pthread.h>

#include <iostream>
#include <string>

#define ID_R_SHOULDER_PITCH 1
#define ID_L_SHOULDER_PITCH 2
#define ID_R_SHOULDER_ROLL 3
#define ID_L_SHOULDER_ROLL 4
#define ID_R_ELBOW 5
#define ID_L_ELBOW 6
#define ID_R_HIP_YAW 7
#define ID_L_HIP_YAW 8
#define ID_R_HIP_ROLL 9
#define ID_L_HIP_ROLL 10
#define ID_R_HIP_PITCH 11
#define ID_L_HIP_PITCH 12
#define ID_R_KNEE 13
#define ID_L_KNEE 14
#define ID_R_ANKLE_PITCH 15
#define ID_L_ANKLE_PITCH 16
#define ID_R_ANKLE_ROLL 17
#define ID_L_ANKLE_ROLL 18
#define ID_HEAD_PAN 19
#define ID_HEAD_TILT 20
#define NUMBER_OF_JOINTS 21

#define P_TORQUE_ENABLE 24
#define P_P_GAIN 28
#define P_GOAL_POSITION_L 30
#define P_PRESENT_POSITION_L 36

#define P_DXL_POWER 24
#define P_LED_HEAD_L 26
#define P_LED_EYE_L 28

#define ID_CM 200

class HDS
{
public:
	Connection _connection;

	HDS(std::string portname);
	~HDS();
	// Sets P_GAIN for the arm and leg servomotors, runs the dxlPowerOn method and locks the legs
	void init();
	// Puts Darwin in its starting position
	void beginPosition();
	// Actions
	void shouldersUp();
	void shouldersDown();
	void shouldersInward();
	void shouldersOutward();
	void elbowsUp();
	void elbowsDown();
	// Performs a transition from the communication server
	void makeTransition(std::string trans);

private:
	// Moves the servomotor to the given goal position
	bool moveServo(unsigned char id, int value);
	// Reads the present position of the servomotor and returns it
	int readServo(unsigned char id);
	// Reads value of a servo and writes the value back to lock the servomotor in its place
	bool readMoveServo(unsigned char id);
	// Performs an action and returns when the goal position is reached
	void doPollMove(unsigned char id, int value);
	// Turns power on for all servomotors
	bool dxlPowerOn();
};

#endif
