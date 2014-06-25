#ifndef FLEXIFORCE_H
#define FLEXIFORCE_H


// SERIAL PORT STUFF
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#define FF_SF2  -0.0014
#define FF_SF    2.1661
#define FF_OFF  -292.6009
#define ACC_G      9.79         // m/(s^2)

#define NEED_FILE 0
#define FLEXI_FILE_PATH   "loadcell_log.txt"

static FILE* flexiforce_file;
static unsigned int flexiforce_val;

static int fd; // file description for the serial port
static int bytes;
static char buffer[5];

void init_flexiforce();
void close_flexiforce();
void get_current_force(double*);
int read_flexiforce();


/*
#include <stdio.h>
#include <math.h>
#include <phidget21.h>

#define DATARATE_ADC_MS 2	            // 500 Hz

#define FF_SF2  -0.0014
#define FF_SF    2.1661
#define FF_OFF  -292.6009
#define ACC_G      9.79         // m/(s^2)

#define NEED_FILE 0
#define FLEXI_FILE_PATH   "loadcell_log.txt"

static FILE* flexiforce_file;
static unsigned int flexiforce_val;

void init_flexiforce(CPhidgetInterfaceKitHandle*);
void close_flexiforce(CPhidgetInterfaceKitHandle*);
void get_current_force(CPhidgetInterfaceKitHandle*, double*);
int read_flexiforce(CPhidgetInterfaceKitHandle, double*);
*/

#endif // FLEXIFORCE_H
