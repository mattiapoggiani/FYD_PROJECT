#ifndef LOADCELL_H
#define LOADCELL_H

#include <stdio.h>
#include <unistd.h>
#include <phidget21.h>

#define LC_SF   -950.7914//-518.3574       // Load cell scale factor
#define LC_OFF   1386.88//657.5965       // Load cell measures offset
#define ACC_G      9.79         // m/(s^2)

#define NEED_FILE 0
#define LOADCELL_FILE_PATH   "loadcell_log.txt"

static FILE* loadcell_file;
static double loadcell_val;

void init_loadcell(CPhidgetBridgeHandle*);
int CCONV data(CPhidgetBridgeHandle, void*, int, double);
void close_loadcell(CPhidgetBridgeHandle*);
void get_current_force(double*);

#endif
