#include "accelerometers.h"

void init_accelerometers(CPhidgetSpatialHandle* spatial){

    	//Create the Spatial object
	CPhidgetSpatial_create(spatial);

    //Registers a callback that will run according to the set data rate that will return the spatial data changes
    //Requires the handle for the Spatial, the callback handler function that will be called,
    //and an arbitrary pointer that will be supplied to the callback function (may be NULL)
    CPhidgetSpatial_set_OnSpatialData_Handler(*spatial, SpatialDataHandler, NULL);

	//Open the Spatial for device connections
	CPhidget_open((CPhidgetHandle)*spatial, -1);

    acc_file = fopen(ACCELER_FILE_PATH, "w");

	// Wait for the sensors to be ready
	sleep(1);

}

//callback that will run at datarate
//data - array of spatial event data structures that holds the spatial data packets that were sent in this event
//count - the number of spatial data event packets included in this event
int CCONV SpatialDataHandler(CPhidgetSpatialHandle spatial, void *userptr, CPhidgetSpatial_SpatialEventDataHandle *data, int count)
{
    new_count = count;
    for(int i = 0; i < count; i++)
    {
        raw_acc[i][0] = ((int)data[i]->acceleration[0]); //*100)/100.0;
        raw_acc[i][1] = ((int)data[i]->acceleration[1]); //*100)/100.0;
        raw_acc[i][2] = ((int)data[i]->acceleration[2]); //*100)/100.0;

        unsigned long int time_us = data[i]->timestamp.seconds*1000000+data[i]->timestamp.microseconds;

        fprintf(acc_file, "%lu:%.6f;%.6f;%.6f\n", time_us, raw_acc[i][0], raw_acc[i][1], raw_acc[i][2]);

    }
    new_dataset = true;

    return 0;
}

// Return current indentation in mm
void get_current_acceleration(short int* acc){
    static int idx = 0;

    if (new_dataset)
        idx = 0;
    else
        idx = (idx+1)%new_count;

    new_dataset = false;

    if(raw_acc[idx][0]){
        for (int i=0; i<3; i++){
          acc[i] = (short int)(ACCEL_SF * raw_acc[idx][i]) - rest_acc[i];		// accelerations are in adimensional unit
        }
    }
}

void close_acc_file(){
    fclose(acc_file);
}
