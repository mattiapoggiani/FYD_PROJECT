#include "flexiforce.h"

int read_flexiforce()
{
    write (fd, "?", 1);           // send 1 character greeting
    read(fd, buffer, sizeof(buffer));

//    printf("read is %s\n", buffer);

    flexiforce_val = atoi(buffer);
    if (flexiforce_val < 0)
           flexiforce_val = 0;

    if (NEED_FILE)
        fprintf(flexiforce_file, "%u\n", flexiforce_val);
    return 0;
}

void init_flexiforce(){
        fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);

        if(fd == -1) // if open is unsucessful
        {
            printf("open_port: Unable to open /dev/ttyACM0. \n");
        }
        else
        {
            fcntl(fd, F_SETFL, 0);
            printf("port is open.\n");
        }

        struct termios port_settings;      // structure to store the port settings in

        cfsetispeed(&port_settings, B115200);    // set baud rates
        cfsetospeed(&port_settings, B115200);

        port_settings.c_cflag &= ~(PARENB | PARODD);    // set no parity, stop bits, data bits
        //port_settings.c_cflag &= ~CSTOPB;
        port_settings.c_cflag &= ~CSIZE;
        port_settings.c_cflag |= CS8;

        tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port
}

void close_flexiforce(){
    close(fd);
    if (NEED_FILE)
        fclose(flexiforce_file);
}

void get_current_force(double* force){
   read_flexiforce();
   *force = (double)(((FF_SF2*flexiforce_val*flexiforce_val + FF_SF*flexiforce_val + FF_OFF)/1000.0)*ACC_G);  // g --> Newton
}


/*
#include "flexiforce.h"
#include <unistd.h>

int read_flexiforce(CPhidgetInterfaceKitHandle ifKit)
{
    int sensorValue;
    CPhidgetInterfaceKit_getSensorValue(ifKit,0, &sensorValue);
       printf("read is %d\n", sensorValue);
    return sensorValue;
}

void init_flexiforce(CPhidgetInterfaceKitHandle* ifKit){

    //Create the InterfaceKit object
    CPhidgetInterfaceKit_create(ifKit);

    //Open the InterfaceKit for device connections
    CPhidget_open((CPhidgetHandle)*ifKit, -1);

    CPhidgetInterfaceKit_setRatiometric(*ifKit, 0);

    //Set Data Rate on InterfaceKit analog sensors
    CPhidgetInterfaceKit_setDataRate(*ifKit, 0, DATARATE_ADC_MS);

    // Wait for the sensors to be ready
    sleep(1);

}

void close_flexiforce(CPhidgetInterfaceKitHandle* ifKit){
    CPhidget_close((CPhidgetHandle)*ifKit);
    CPhidget_delete((CPhidgetHandle)*ifKit);
}

void get_current_force(CPhidgetInterfaceKitHandle* ifKit, double* force){
   flexiforce_val = read_flexiforce(*ifKit);
   *force = (double)(((FF_SF2*flexiforce_val*flexiforce_val + FF_SF*flexiforce_val + FF_OFF)/1000.0)*ACC_G);  // g --> Newton
}
*/
