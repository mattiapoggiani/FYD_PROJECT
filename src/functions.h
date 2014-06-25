#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <sys/time.h>

double set_in_bound(double min, double max);
int isInRange(float, float, float);
void PID_control();
double time_diff(timeval, timeval);

#endif
