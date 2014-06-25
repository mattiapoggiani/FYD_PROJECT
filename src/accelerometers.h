#ifndef ACCELEROMETERS_H
#define ACCELEROMETERS_H

// - Spatial -

#include <stdio.h>
#include <unistd.h>
#include <phidget21.h>

#define DATARATE_MS 1	            // 1000 Hz
#define MAX_SENSOR_ACC_G 5	    // (-5g, +5g)
#define MAX_SENSOR_VALUE 32768	    // 2^15 = 32768, 16 bit integer values
#define ACCEL_SF (MAX_SENSOR_VALUE/MAX_SENSOR_ACC_G) 	// Accelerometers Scale Factor to obtain integer values

#define ACCELER_FILE_PATH   "acceleration_log.txt"

extern short int rest_acc[3];        //{1,0,0};		// X axis is sensing gravity
static double raw_acc[16][3];
static bool new_dataset = false;
static int new_count = 1;
static FILE* acc_file;

void init_accelerometers(CPhidgetSpatialHandle*);
int CCONV SpatialDataHandler(CPhidgetSpatialHandle, void*, CPhidgetSpatial_SpatialEventDataHandle*, int);
void get_current_acceleration(short int*);
void close_acc_file();

#endif
