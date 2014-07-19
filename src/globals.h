#ifndef GLOBALS_H
#define GLOBALS_H

/*** PHANTOM INCLUDES ***/
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <QMainWindow>

/*** APPLICATION INCLUDES & DEFINES ***/
#include "conio.h"
#include "accelerometers.h"
#include "flexiforce.h"
#include "loadcell.h"
#include "wireless_communicator.h"
//#include "/usr/include/opencv2/highgui/highgui.hpp"

#define ENABLE_NETWORK
//#define KUKA
//#define SHOW_IMAGE

#define G_COMP_X  0         //0
#define G_COMP_Y  0.71		//0.51
#define G_COMP_Z  0.15		//-0.15

#define Ki0 0.002		// 0.01 OK
#define Ki2 0.008
#define Kd0 0.000005
#define Kd2 0.000012
#define MAX_I 0.2
#define MAX_FORCE_0 0.3		// N (MAXIMUM FORCE ON PHANTOM: 7.9 N)
#define MAX_FORCE_1 2.0
#define MAX_FORCE_2 0.3
#define MIN_FORCE_N 0.001

#define POSITION_ERROR_THR 0.5 //10//0.01

#define ACCELERATIONS_US 700	//330

#define WALL_STIFFNESS 0.8

#define PHANTOM_FILE_PATH   "phantom_log.txt"

#endif
