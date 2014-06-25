/*****************************************************************************
F.Y.D. Client
*******************************************************************************/
#include "globals.h"
using namespace std;

/*************** NETWORK VARIABLES ***************/
const char* hostname;
char buf[MAXDATASIZE];

/********* APPLICATION GLOBAL VARIABLES **********/
CPhidgetSpatialHandle accel = 0;
short int rest_acc[3];
short int acc[3] = {0,0,0};
short int ref[2] = {0,0};
char imbuf[IMAGESIZE];
char QB_info[1210];
float k_vib;
short int finger[3] = {0,0,0}; //{-PHANTOM0_POS, PHANTOM2_POS, PHANTOM1_POS}; 	// Phantom desired initial position
FILE* ph_file;
short int cmd;
// CMD = 0, obtain only position
// CMD = 1, decrease vibration gain
// CMD = 2, increase vibration gain
// CMD = 3, switch vibration method to DFT321
// CMD = 4, switch vibration method to SoC
// CMD = 5, obtain info QB and pause program
// CMD = 6, restart program
// CMD = 7, begin to send image
// CMD = 8, stop to send image
// CMD = 9, disconnect from server

double CONSTANT_ROBOT_GAIN = 1.0;
double CONSTANT_UPDOWN_GAIN = 1.5;
double MIN_X = CONSTANT_ROBOT_GAIN*(-35);    //-40
double MAX_X = CONSTANT_ROBOT_GAIN*35;    //40
double MIN_Y = -70;     //-100
double MAX_Y =  70;    //100
double MIN_Z = CONSTANT_ROBOT_GAIN*(-25);     //-30
double MAX_Z = CONSTANT_ROBOT_GAIN*25;     //30

double Kp0 = 0.025;           // 0.02 OK
double Kp1 = 0.03;
double Kp2 = 0.02;

/*********** IMAGE GLOBAL VARIABLES *************/
//IplImage* frame = cvCreateImageHeader(cvSize(160,120), IPL_DEPTH_8U, 3);
//CvMat image 	= cvMat(frame->height, frame->width, CV_8UC3, imbuf);

/************ PHANTOM GLOBAL VARIABLES *************/
/*
HDErrorInfo error;
HDSchedulerHandle hloop;
HHD hHD;
hduVector3Dd Pposition;
hduVector3Dd Poffset;
hduVector3Dd finger_position;
hduVector3Dd position_error(0,0,0);
hduVector3Dd force;
HDint buttonState;
double force0, force1, force2;
hduVector3Dd pos_err_int(0,0,0);
hduVector3Dd pos_err_diff(0,0,0), pos_err_last(0,0,0);

HDCallbackCode HDCALLBACK loop(void* data);
*/
int buttonState;
double Pposition[3];

/***************** GLOBAL FLAGS *******************/
int recv_img;
bool recv_info = false;
bool first_run = true;
bool first_run_acc = true;
bool reset_flag = false;
bool vibration_enabled = true;
bool begin_program = true;				// Set to false when having Phantom
bool connected = false;
bool gui_flag = true;
bool send_motor_ref_flag = false;
double force_loadcell;
double stiffness;
double z0;
float indent0 = 0.0;

timeval now, last;
double dt;
QString console_info_str;

FILE* log_file;

#include "LWRCartImpedanceController.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <FastResearchInterface.h>


#define NUMBER_OF_FRAME_ELEMENTS	12
#define NUMBER_OF_CART_DOFS			6
#define NUMBER_OF_JOINTS			7
#define RUN_TIME_IN_SECONDS			1000.0

unsigned int				CycleCounter	=	0
                        ,	i				=	0;

int							ResultValue		=	0;

float						CommandedForcesAndTorques				[NUMBER_OF_CART_DOFS		]
                        ,	CommandedStiffness						[NUMBER_OF_CART_DOFS		]
                        ,	CommandedDamping						[NUMBER_OF_CART_DOFS		]
                        ,	EstimatedExternalCartForcesAndTorques	[NUMBER_OF_CART_DOFS		]
                        ,	CommandedPose							[NUMBER_OF_FRAME_ELEMENTS	]
                        ,	MeasuredPose							[NUMBER_OF_FRAME_ELEMENTS	]
                        ,	ZeroPose                            	[NUMBER_OF_FRAME_ELEMENTS	]
                        ,	InitialPose                            	[NUMBER_OF_FRAME_ELEMENTS	]
                        ,	JointValuesInRad						[NUMBER_OF_JOINTS			]
                        ,	MeasuredJointTorques					[NUMBER_OF_JOINTS			];

LWRCartImpedanceController	*Robot;

using namespace Eigen;

Matrix4f WorldRobotBase = Matrix4f::Identity();

#ifndef PI
#define PI	3.1415926535897932384626433832795
#endif

Matrix4f Home = Matrix4f::Identity();
Matrix4f WorldRobotef = Matrix4f::Identity();
Matrix4f WorldRobotefI = Matrix4f::Identity();
Matrix4f gotoworld = Matrix4f::Identity();
Matrix4f gotRobot = Matrix4f::Identity();
Matrix4f NewRobotef = Matrix4f::Identity();
Matrix4f WorldRobotBaseI =Matrix4f::Identity();

Matrix4f ROTX(float angle){

    Matrix4f Mat = Matrix4f::Identity(4,4);
    Mat(1,1) = cos(angle); Mat(1,2) = -sin(angle);
    Mat(2,1) = sin(angle); Mat(2,2) = cos(angle);

    return Mat;
}

Matrix4f ROTZ(float angle){

    Matrix4f Mat = Matrix4f::Identity(4,4);
    Mat(0,0) = cos(angle); Mat(0,1) = -sin(angle);
    Mat(1,0) = sin(angle); Mat(1,1) = cos(angle);

    return Mat;
}

Matrix4f ROTY(float angle){

    Matrix4f Mat = Matrix4f::Identity(4,4);
    Mat(0,0) = cos(angle); Mat(0,2) = sin(angle);
    Mat(2,0) = -sin(angle); Mat(2,2) = cos(angle);

    return Mat;
}

float get_material_stiffness(){
    // Move KUKA downwards until 10 stiffness samples are in memory
    int count = 0;
    float indent = 0.0;
    float inc = 0.0;
    double stiffness[10];
    double force_flexi = 0.0;

    // FLEXIFORCE INITIALIZATION
    init_flexiforce();

    Robot->GetMeasuredCartPose (MeasuredPose);

    while (count<10 && indent<10){

        inc -= 0.001;

        gotoworld(0, 3) = 0;
        gotoworld(1, 3) = 0;
        gotoworld(2, 3) = inc + 0.001*z0;
        gotRobot.block<3,1>(0,3) = (WorldRobotef.block<3,3>(0,0)).inverse()*gotoworld.block<3,1>(0,3);
        NewRobotef = WorldRobotBaseI*(WorldRobotef*gotRobot);

        int index_matrix = 0;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 4; j++){
                CommandedPose[index_matrix] = NewRobotef(i,j);
                index_matrix++;
            }
        }
        Robot->SetCommandedCartPose( CommandedPose );
        usleep(500000);

        get_current_force(&force_flexi);

        if (force_flexi > 0.1){
            // It is a valid measure
            if (count == 0){
                indent0 = inc;
            }
            indent = fabs(inc) - fabs(indent0);

            stiffness[count] = force_flexi / (indent*1000);
            count++;
        }
       cout << "INC: " << inc << " - INDENT: " << indent << "INDENT0: " << indent0 << " COUNT: " << count << endl;
//        cout << "FORCE: " << force_flexi << endl;
//        cout << "STIFFNESS: " << stiffness[count-1] << endl << endl;
    }

    // Average stiffness samples
    double stiff = 0;
    for (int i=1; i<count; i++){
        stiff += stiffness[i];
    }
    stiff /= count;


    // Close flexiforce
    close_flexiforce();

    // Get starting position
    Robot->SetCommandedCartPose( MeasuredPose );

    return stiff;
}


void* packets_loop(void* data){
    short int finger_old[3] = {0,0,0};
    double force_old = 0;

    timeval start, start_old;
    uint32_t diff = 0;

    while(connected){
        gettimeofday(&start, NULL);
        diff = time_diff(start_old, start);
        start_old.tv_sec = start.tv_sec; start_old.tv_usec = start.tv_usec;
//        cout << "DIFF: " << diff << endl;
        if (ACCELERATIONS_US >= diff)
            usleep(ACCELERATIONS_US - diff);
        if (begin_program){

            if (vibration_enabled){
                // Read accelerations
                get_current_acceleration(acc);
            }
            else{
                acc[0] = acc[1] = acc[2] = 0;
            }

            // Send accelerations
            create_packet(buf, acc, (unsigned int)buttonState, (double*)&Pposition, stiffness);
            send_data(buf);

            if (!connected) break;

            if (receive_packet() && !reset_flag) {
//                cout << "RECV: " << finger[0] << "; " << finger[1] << "; " << finger[2] << endl;
//                cout << "FORCE: " << force_loadcell << endl;

                if ((!finger[0] && !finger[1]) ){ //|| (force_loadcell > 0.1)){
                        finger[0] = finger_old[0];
                    finger[1] = finger_old[1];
                }
                else {
                    finger[0] = 0.8*finger_old[0] + 0.2*finger[0];
                    finger[1] = 0.8*finger_old[1] + 0.2*finger[1];
                }

                if (finger[0] && finger[1] && (finger[2] > 0.0))	//descent phase
                    finger[2] = finger_old[2];
                else
                    finger[2] = 0.9*finger_old[2] + 0.1*finger[2];

                if (force_loadcell > MIN_FORCE_N)
                    force_loadcell = 0.8*force_old + 0.2*force_loadcell;
                else
                    force_loadcell = 0;

                finger_old[0] = finger[0];
                finger_old[1] = finger[1];
                finger_old[2] = finger[2];
                force_old = force_loadcell;

                finger[0] *= CONSTANT_ROBOT_GAIN;
                finger[1] *= CONSTANT_ROBOT_GAIN;
                finger[2] *= CONSTANT_UPDOWN_GAIN;

            }
            else{
                if (reset_flag){
                    finger[0] = finger[1] = finger[2] = 0;
                }
            }

//            cout << "POSITION - X: "  << finger[0] << " Y - " << finger[1] << endl;
//            cout << "INDENTATION: " << finger[2] << endl;
//            cout << "FORCE: " << force_loadcell << endl << endl;
cout << "FINGER - x: " << finger[0] << ", y: " << finger[1] << ", z: " << finger[2] << endl;
            // Other Requests
            if (recv_info){
                if(receive_info(QB_info, &k_vib, ref)){
                    if (gui_flag)
                        console_info_str = QString(QB_info);
                    else
                        cout << QB_info << endl;
                }
                recv_info = false;
            }
#ifdef SHOW_IMAGE
            // RECEIVE IMAGE
            if (recv_img == 1){
                if (receive_image())
                    frame = cvDecodeImage(&image, CV_LOAD_IMAGE_COLOR);
                    cvFlip(frame, frame, 1);        // Flip image around Y axis
/*                    if(!gui_flag){
                        cvNamedWindow("Application", CV_WINDOW_AUTOSIZE);
                        cvShowImage("Application", frame);
                        cvWaitKey(1);
                    }
*/            }
#endif
            if (send_motor_ref_flag){
                create_motor_ref_packet(buf, ref);
                send_motor_ref(buf);
                send_motor_ref_flag = false;
            }
        }
    }

    pthread_exit(NULL);

}

void* kuka_thread(void* data){

    double gotoworld_old[3];
    double finger_old[3];
    double diff[3];

    while (1)   //((float)CycleCounter * Robot->GetCycleTime() < RUN_TIME_IN_SECONDS)
    {

        // Set rest acceleration before starting vibration
        if (first_run_acc){
            get_current_acceleration(rest_acc);
            first_run_acc = false;
        }

        Robot->WaitForKRCTick();

        if (!Robot->IsMachineOK())
        {
            fprintf(stderr, "ERROR, the machine is not ready anymore.\n");
            break;
        }

        Robot->GetMeasuredCartPose( MeasuredPose );
        Matrix4f MeasuredMatrix = Matrix4f::Identity();
        int index_matrix = 0;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 4; j++){
                MeasuredMatrix(i,j) = MeasuredPose[index_matrix];
                index_matrix++;
            }
        }
        NewRobotef = WorldRobotefI*(WorldRobotBase*MeasuredMatrix);
        index_matrix = 0;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 4; j++){
                MeasuredPose[index_matrix] = NewRobotef(i,j);
                index_matrix++;
            }
        }
/*
        for(int i=0; i<12; i++){
            fprintf(log_file, "%.6f", MeasuredPose[i]);
            if (i<11) fprintf(log_file, ";");
        }
        fprintf(log_file, "\n");
*/

        fprintf(log_file, "%.6f;%.6f;%.6f;", 1000*MeasuredPose[3], 1000*MeasuredPose[7], 1000*MeasuredPose[11]);
        fprintf(log_file, "%hd;%hd;%hd\n", finger[0], finger[1], finger[2]);

//        std::cout << "POSE: " << MeasuredPose[3] << "; " << MeasuredPose[7] << "; " << MeasuredPose[11] << std::endl;

 //       cout << "FINGER - x: " << finger[0] << ", y: " << finger[1] << ", z: " << finger[2] << endl;
//        gotoworld(0, 3) = 0.001 * (-finger[1]);
//        gotoworld(1, 3) = 0.001 * (-finger[0]);
//        gotoworld(2, 3) = 0.001 * (finger[2]);

        gotoworld(0, 3) = 0.001 * (-(0.99*finger_old[1] + 0.01*finger[1]));
        gotoworld(1, 3) = 0.001 * (-(0.99*finger_old[0] + 0.01*finger[0]));
        gotoworld(2, 3) = 0.002 * ((0.99*finger_old[2] + 0.01*finger[2])) + (0.001*z0+indent0+0.013); //+indent0+0.005);

        gotRobot.block<3,1>(0,3) = (WorldRobotef.block<3,3>(0,0)).inverse()*gotoworld.block<3,1>(0,3);

        NewRobotef = WorldRobotBaseI*(WorldRobotef*gotRobot);

        index_matrix = 0;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 4; j++){
                CommandedPose[index_matrix] = NewRobotef(i,j);
                index_matrix++;
            }
        }

//        Robot->GetMeasuredJointTorques					(MeasuredJointTorques					);
//        Robot->GetMeasuredJointPositions				(JointValuesInRad						);
 //       Robot->GetMeasuredCartPose						(MeasuredPose							);
//        Robot->GetEstimatedExternalCartForcesAndTorques	(EstimatedExternalCartForcesAndTorques	);


//        CommandedPose[3] = MeasuredPose[3] + 0.001*finger[0];
//        CommandedPose[7] = MeasuredPose[7] + 0.001*finger[1]; // 0.005;
//        CommandedPose[11] = MeasuredPose[11] + 0.001*finger[2]; // 0.005;

        diff[0] = fabs(gotoworld_old[0] - gotoworld(0,3));
        diff[1] = fabs(gotoworld_old[1] - gotoworld(1,3));
        diff[2] = fabs(gotoworld_old[2] - gotoworld(2,3));
/*
        if (diff[0] > 10)
            CommandedDamping[0]	= (float)0.6;
        else
            CommandedDamping[0]	= (float)0.3;

        if (diff[1] > 10)
            CommandedDamping[1]	= (float)0.6;
        else
            CommandedDamping[1]	= (float)0.3;

        if (diff[2] > 10)
            CommandedDamping[2]	= (float)0.6;
        else
            CommandedDamping[2]	= (float)0.3;

        Robot->SetCommandedCartDamping	 ( CommandedDamping	);
*/

        Robot->SetCommandedCartPose( CommandedPose );

 //       std::cout << "COMMAND: " << CommandedPose[3] << "; " << CommandedPose[7] << "; " << CommandedPose[11] << std::endl << std::endl;
        finger_old[0] = finger[0];
        finger_old[1] = finger[1];
        finger_old[2] = finger[2];

//        gotoworld_old[0] = gotoworld(0,3);
        //gotoworld_old[1] = gotoworld(1,3);
        //gotoworld_old[2] = gotoworld(2,3);

        CycleCounter++;
    }

    fprintf(stdout, "Stopping the robot...\n");
    ResultValue	=	Robot->StopRobot();

    if (ResultValue != EOK)
    {
        fprintf(stderr, "An error occurred during stopping the robot...\n");
    }
    else
    {
        fprintf(stdout, "Robot successfully stopped.\n");
    }

    pthread_exit(NULL);       cout << "ACC: " << acc[0] << "; " << acc[1] << "; " << acc[2] << endl;
}

/*******************************************************************************
 This function initializes the device, starts the schedule and creates a schedule callback
 to handle phantom.
*******************************************************************************/
int phantom_init(int mode, const char* ip_host, double z0_var){

        std::cout << "Robot Initialization" << std::endl;
        z0 = z0_var;

        log_file = fopen("log.csv", "w");

#ifdef KUKA
        Robot	=	new LWRCartImpedanceController("input_files/980241-FRI-Driver.init");

        fprintf(stdout, "RobotCartImpedanceController object created. Starting the robot...\n");

        ResultValue	=	Robot->StartRobot();

        if (ResultValue == EOK)
        {
            fprintf(stdout, "Robot successfully started.\n");
        }
        else
        {
            fprintf(stderr, "ERROR, could not start robot: %s\n", strerror(ResultValue));
        }

        fprintf(stdout, "Current system state:\n%s\n", Robot->GetCompleteRobotStateAndInformation());

        for (i = 0; i < NUMBER_OF_CART_DOFS; i++)
        {
            if (i<=2)
                CommandedStiffness			[i]	= (float)1000.0;
            else
                CommandedStiffness          [i] = (float)300.0;
            CommandedDamping			[i]	=	(float)0.3;
            CommandedForcesAndTorques	[i]	=	(float)0.0;
        }

        Robot->GetMeasuredCartPose( ZeroPose );


        Robot->SetCommandedCartStiffness ( CommandedStiffness );
        Robot->SetCommandedCartDamping	 ( CommandedDamping	);
        Robot->SetCommandedCartForcesAndTorques	( CommandedForcesAndTorques	);
        Robot->SetCommandedCartPose( ZeroPose );




        // A: 180 deg, B: 0 deg, C: 180 deg

        /*
        ZeroPose[0] = -0.497;
        ZeroPose[1] =  0.435;
        ZeroPose[2] =  0.751;
        ZeroPose[3] =  -0.008;
        ZeroPose[4] =  0.868;
        ZeroPose[5] =  0.254;
        ZeroPose[6] =  0.427;
        ZeroPose[7] =  0.719;
        ZeroPose[8] =  -0.005;
        ZeroPose[9] =  0.864;
        ZeroPose[10] = -0.504;
        ZeroPose[11] = 0.036;
*/
/*      POSITION OK     */
        ZeroPose[0] = -0.485;
        ZeroPose[1] =  0.45;
        ZeroPose[2] =  0.75;
        ZeroPose[3] =  -0.020;
        ZeroPose[4] =  0.874;
        ZeroPose[5] =  0.227;
        ZeroPose[6] =  0.429;
        ZeroPose[7] =  0.723;
        ZeroPose[8] =  -0.023;
        ZeroPose[9] =  0.864;
        ZeroPose[10] = -0.503;
        ZeroPose[11] = 0.057;

/*
        // POSITION FOR CORRELATION TESTS
                ZeroPose[0] = -0.476;
                ZeroPose[1] =  0.441;
                ZeroPose[2] =  0.761;
                ZeroPose[3] =  -0.027;
                ZeroPose[4] =  0.879;
                ZeroPose[5] =  0.251;
                ZeroPose[6] =  0.404;
                ZeroPose[7] =  0.713;
                ZeroPose[8] =  -0.013;
                ZeroPose[9] =  0.862;
                ZeroPose[10] = -0.507;
                ZeroPose[11] = 0.059;
*/
        Robot->SetCommandedCartPose( ZeroPose );

        sleep(1);

        // Get starting position
        Robot->GetMeasuredCartPose( ZeroPose );

        WorldRobotBase	 = ROTX(-60.*PI/180.)*ROTZ(60.*PI/180.);

        int irobot = 0;
            for(int irow=0; irow<3; ++irow){
              for(int icol=0; icol<4; ++icol){
                Home(irow, icol) = ZeroPose[irobot];
                ++irobot;
            }
        }
#endif
        WorldRobotBaseI = WorldRobotBase.inverse();
        WorldRobotef = WorldRobotBase*Home;
        WorldRobotefI = WorldRobotef.inverse();
        NewRobotef = Home;
        std::cout << "Home transformation :"<< Home << std::endl;

        fprintf(stdout, "Performing Cartesian impedance control.\n");

        cout << "Getting stiffness information ...";
        stiffness = get_material_stiffness(); //0.7; //1.0;
        cout << "done." << endl;

        cout << "STIFFNESS: " << stiffness << endl << endl;



    printf("F.Y.D. Client application\n");

/*********************** INITIALIZE CONNECTION WITH F.Y.D. *********************/
#ifdef ENABLE_NETWORK

    switch(mode){
        case 0:     hostname = "192.168.0.100";     // Ethernet connection
                    break;
        case 1:     hostname = "10.42.0.1";         // FYD Touch wireless network
                    break;
        default:    hostname = ip_host;             // Other IP address (only if there is no gui)
                    break;
    }

    // Retrieve server address
    if (initialize_connection()){
        cout << "Error creating connection with " << hostname << endl;
        return 1;
    }

    strcpy(buf, "ACK");     // Initial handshake
    send_data(buf);

    receive_info(QB_info, &k_vib, ref);

    if (mode==1)
        set_recv_timeout();

	connected = true;

    buttonState = true;

#endif

#ifdef SHOW_IMAGE
/******************* CREATE PROGRAM VARIABLES **********************/
    cvSetData(frame, (void*)imbuf, CV_AUTOSTEP);
#endif

/****************** CREATE ACCELEROMETERS VARIABLES ******************/
	init_accelerometers(&accel);
    CPhidgetSpatial_setDataRate(accel, DATARATE_MS);

/*********************** START PHANTOM PROCESS **************************/
    ph_file = fopen(PHANTOM_FILE_PATH, "w");

//	pos_err_int[0] = pos_err_int[1] = pos_err_int[2] = 0;

/********************* START SEND/RECV PACKETS *******************/
#ifdef ENABLE_NETWORK
	pthread_t packets_thr;
	if (pthread_create(&packets_thr, NULL, packets_loop, (void*)3)){
		cout << "Error creating F.Y.D. Client thread" << endl;
		return 1;
	}
#endif

#ifdef KUKA
    pthread_t kuka_thr;
    double* z0_p = &z0;
    if (pthread_create(&kuka_thr, NULL, kuka_thread, (void*)z0_p)){
        cout << "Error creating KUKA thread" << endl;
        return 1;
    }

#endif

   return 0;
}
/*******************************************************************************
 This function closes the device and exits the application.
*******************************************************************************/
int phantom_close(){
/********************** CLOSE CONNECTION WITH F.Y.D. AND PHANTOM ********************/
    fclose(log_file);

#ifdef KUKA
    fprintf(stdout, "Deleting the object...\n");
    delete Robot;
    fprintf(stdout, "Object deleted...\n");
#endif

    close_acc_file();
    fclose(ph_file);

#ifdef ENABLE_NETWORK
    /* Close connection with F.Y.D. */
    close_connection();
#endif

    // Detach and close Accelerometers
    CPhidget_close((CPhidgetHandle)accel);
    CPhidget_delete((CPhidgetHandle)accel);

    cout << "PHANTOM application terminated successfully" << endl;
    return 0;
}




//    if (first_run) {
//        first_run = false;
//        hduVecSet(Poffset, Pposition[0], Pposition[1], Pposition[2]);
//        hdEndFrame(hHD);
//        return HD_CALLBACK_CONTINUE;
//    }


//    if (!reset_flag){
        // Change of coordinates because of differen frame definitions
        // Phantom frame: X (right), Y(up), Z(front)
        // F.Y.D. frame: X (right), Y(back), Z(up)
//        hduVecSet(finger_position, finger[0], finger[2], finger[1]);
//    }
//    else {
//        finger_position[0] = -PHANTOM0_POS;
//        finger_position[2] =  PHANTOM2_POS;
//    }



         // Set begin_program flag to start communication with F.Y.D. device
//         if (!begin_program) begin_program = true;

//         reset_flag = false;


//}

/*****************************************************************************/
