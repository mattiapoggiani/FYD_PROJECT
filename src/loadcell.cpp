#include "loadcell.h"

int CCONV data(CPhidgetBridgeHandle phid, void *userPtr, int index, double val)
{
    loadcell_val = val;
    if (NEED_FILE)
        fprintf(loadcell_file, "%.6f\n", val);
    return 0;
}

int CCONV AttachHandler(CPhidgetHandle phid, void *userptr)
{
    CPhidgetBridgeHandle bridge = (CPhidgetBridgeHandle)phid;

    CPhidgetBridge_setEnabled(bridge, 0, PFALSE);
    CPhidgetBridge_setEnabled(bridge, 1, PFALSE);
    CPhidgetBridge_setEnabled(bridge, 2, PFALSE);
    CPhidgetBridge_setEnabled(bridge, 3, PTRUE);

    CPhidgetBridge_setGain(bridge, 3, PHIDGET_BRIDGE_GAIN_128);
    CPhidgetBridge_setDataRate(bridge, 10);

    printf("Attach handler ran!\n");
    return 0;
}

void init_loadcell(CPhidgetBridgeHandle* bridge){

    CPhidgetBridge_create(bridge);

    CPhidget_set_OnAttach_Handler((CPhidgetHandle)bridge, AttachHandler, NULL);

    CPhidgetBridge_set_OnBridgeData_Handler(*bridge, data, NULL);

    CPhidget_open((CPhidgetHandle)*bridge, -1);

    if (NEED_FILE)
        loadcell_file = fopen(LOADCELL_FILE_PATH, "w");

    // Wait for the sensors to be ready
    sleep(1);

}

void close_loadcell(CPhidgetBridgeHandle* bridge){
    CPhidget_close((CPhidgetHandle)bridge);
    CPhidget_delete((CPhidgetHandle)bridge);
    if (NEED_FILE)
        fclose(loadcell_file);
}

void get_current_force(double* force){
   *force = (double)(((LC_SF*loadcell_val + LC_OFF)/1000.0)*ACC_G);  // g --> Newton
}
