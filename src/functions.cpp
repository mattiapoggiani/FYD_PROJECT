 #include "functions.h"

double time_diff(timeval x, timeval y){
    double x_us, y_us, diff;

    x_us = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_us = (double)y.tv_sec*1000000 + (double)y.tv_usec;

    diff = (double)y_us - (double)x_us;

    return diff;
}

int isInRange(float x, float MIN, float MAX){
    if (x>MAX)
        return 1;
    else {
        if (x<MIN)
            return -1;
        else
            return 0;
    }
}
