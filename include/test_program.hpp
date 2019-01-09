#ifndef _TEST_PROGRAM_HPP_
#define _TEST_PROGRAM_HPP_

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

#endif
