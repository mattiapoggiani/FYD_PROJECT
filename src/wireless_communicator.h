// Wireless communicator - Client part

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "functions.h"

#define sign(X) (X>=0.0)?48:49

#define PORT 3490     // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once
#define IMAGESIZE 57600//307200
using namespace std;

extern const char* hostname;
static int sockfd;
static int numbytes;
extern char buf[MAXDATASIZE];
static sockaddr_in server;
static int len;
static char QB_string[1210];
static char info_str[2000];

extern char imbuf[IMAGESIZE];
extern int recv_img;
extern bool recv_info;
extern short int finger[3];
extern double force_loadcell;
extern short int cmd;
extern bool connected;
extern bool send_motor_ref_flag;

void* get_in_addr(sockaddr* sa);    // get sockaddr IPv4 or IPv6
int initialize_connection();
void close_connection();

void set_recv_timeout();
bool parse_packet();
bool parse_info(float*);
void receive_data();
void send_data(char*);
bool receive_packet();
bool receive_string();
void create_packet(char*, short int*, short int, double*, double);
bool receive_image();
bool receive_info(char*, float*, short int*);
void create_motor_ref_packet(char*, short int*);
void send_motor_ref(char*);
