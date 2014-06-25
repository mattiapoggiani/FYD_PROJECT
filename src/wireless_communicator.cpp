// Wireless communicator - Client part

#include "wireless_communicator.h"

int initialize_connection(){
    hostent* host;
    host = gethostbyname(hostname);
    len = sizeof(struct sockaddr_in);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
            perror("client: socket");
            exit(1);
    }

    memset((char *)&server, 0, sizeof(server)); 
    server.sin_family = AF_INET; 
    server.sin_addr = *((struct in_addr*) host->h_addr);
    server.sin_port = htons(PORT); 

    cout << "client: connecting to " << inet_ntoa(server.sin_addr) << endl;

    sockaddr_in myaddr;
    memset((char *)&myaddr, 0, sizeof(myaddr)); 
    myaddr.sin_family = AF_INET; 
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    myaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) { 
    	perror("client: bind failed"); 
    	exit(1);
    }

    return 0;
}

void set_recv_timeout(){
    timeval timeout;
    timeout.tv_sec  = 1;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (timeval*)&timeout, sizeof(timeval));
}

void close_connection(){
    cmd = 9;
    sleep(3);		// Time to send disconnection command to server
    connected = false;
    close(sockfd);
}

bool parse_packet(){
    char signs[4] = {0,0,0,0};
    short int args[4] = {0,0,0,0};
    // Check if the packet is valid
    if (buf[0] != '?')
        return false;
    char* pbuf = &buf[1];
    int ret = sscanf(pbuf, "%c'%05hd:%c'%05hd:%c'%05hd:%c'%05hd.", &signs[0], &args[0], &signs[1], &args[1], &signs[2], &args[2], &signs[3], &args[3]);
    if (ret != 8)
            return false;
    else{
    for (int i=0; i<4; i++){
		if (signs[i] == '1')
			args[i] = -args[i];
		else if (signs[i] != '0')
			return false;
	}
    }
    finger[0] = args[0];
    finger[1] = args[1];
    finger[2] = args[2];
    force_loadcell = double(args[3]/10000.0);

    return true;

}

bool parse_info(float* k_vib, short int* ref){
    // Check if the packet is valid
    unsigned int val_k;
    char signs[2] = {0,0};
    int ret = sscanf(info_str, "^%3d^%c'%05hd^%c'%05hd", &val_k, &signs[0], &ref[0], &signs[1], &ref[1]);
    if (ret != 5)
        return false;
    else {
        *k_vib = ((int)val_k)/10.0;
        if (signs[0] == '1')
            ref[0] = -ref[0];
        if (signs[1] == '1')
            ref[1] = -ref[1];
        return true;
    }
}

void receive_data(){
    memset(&buf, 0, sizeof(buf));
    // Receive data
    numbytes = recvfrom(sockfd, buf, 34, MSG_WAITALL, (sockaddr*)&server, (socklen_t*)&len);
    if (numbytes == -1 || numbytes < 34){
//            perror("recv");
            numbytes = recvfrom(sockfd, buf, 34, MSG_WAITALL, (sockaddr*)&server, (socklen_t*)&len);
	}
    buf[numbytes] = '\0';
}

void send_data(char* var){
    int ret = sendto(sockfd, (void*)var, 62, MSG_WAITALL, (sockaddr*)&server, len);
    if (ret == -1 || ret < 62){
		perror("send");
		exit(1);
	}
}

void create_packet(char* str, short int* val, short int button, double* pos, double stiff){
	char app[MAXDATASIZE] = "?";
	char s[MAXDATASIZE];
	sprintf(s, "%c,", (char)cmd+48);
	strcat(app, s);
	for (int i=0; i<3; i++){
		sprintf(s, "%c'%05d", (sign(val[i])), abs(val[i]));
		strcat(app, s);
		strcat(app, ":");
	}
	sprintf(s, "%c,", (char)button+48);
	strcat(app, s);
	for (int i=0; i<3; i++){
		sprintf(s,"%c'%05d", (sign(pos[i])), (short int)(abs(pos[i])));
		strcat(app, s);
        strcat(app, ":");
    }
    sprintf(s, "%c'%05d", (sign(stiff)), (short int)(abs(10000*stiff)));
    strcat(app, s);
	strcat(app, ".\n");

    // packet: ?cmd,accX:accY:accZ:button,posX:posY:posZ:stiffness.
	switch (cmd){
        case 0:
			break;
        case 1: case 2:
            break;
        case 3: case 4:
            break;
        case 5:		// stop F.Y.D. code
            recv_info = true;
			break;
        case 6:
            recv_info = false;
            break;
		case 7:	recv_img = 1;
			break;
		case 8:	recv_img = 0;
			break;
		case 9:	// close connection
			break;
        case 10: send_motor_ref_flag = true;
                break;
        case 11: send_motor_ref_flag = false;
                break;
        default:
			break;
	}

	strcpy(str, app);

	// Reset command
	cmd = 0;
}

bool receive_image(){
    unsigned int imgSize;
    char buf[10];
    numbytes = recvfrom(sockfd, &buf, 6, MSG_WAITALL, (sockaddr*)&server, (socklen_t*)&len);
    if (numbytes == -1 || numbytes < 6){
		perror("recv");
        return false;
	}
    sscanf(buf, "%06d", &imgSize);
    numbytes = 0;
    for(unsigned int i=0; i < imgSize; i+=numbytes){
        if ((numbytes = recvfrom(sockfd, imbuf+i, imgSize-i, 0, (sockaddr*)&server, (socklen_t*)&len)) == -1){
            perror("recv");
            return false;
        }
    }
    imbuf[numbytes] = '\0';
    return true;
}

bool receive_string(){
    unsigned int mex_len;
    char buf[5];
    numbytes = recvfrom(sockfd, &buf, 5, MSG_WAITALL, (sockaddr*)&server, (socklen_t*)&len);
    if (numbytes == -1 || numbytes < 5){
        perror("recv");
            return false;
    }
    sscanf(buf, "%05d", &mex_len);
    numbytes = recvfrom(sockfd, QB_string, mex_len, MSG_WAITALL, (sockaddr*)&server, (socklen_t*)&len);
    if (numbytes == -1 || numbytes < (int)mex_len){
            perror("recv");
            return false;
    }
    QB_string[numbytes] = '\0';

    numbytes = recvfrom(sockfd, info_str, 20, MSG_WAITALL, (sockaddr*)&server, (socklen_t*)&len);
    if (numbytes == -1 || numbytes < 20){
            perror("recv");
            return false;
    }
    info_str[numbytes] = '\0';

    return true;
}

bool receive_packet(){
	receive_data();
    return parse_packet();
}

bool receive_info(char* info, float* arg1, short int* ref){
    receive_string();
    strcpy(info, QB_string);
    return parse_info(arg1, ref);
}

void create_motor_ref_packet(char* str, short int* val){
    char app[MAXDATASIZE] = "";
    char s[MAXDATASIZE];
    sprintf(s, "%c'%05d", (sign(val[0])), abs(val[0]));
    strcat(app, s);
    strcat(app, ":");
    sprintf(s, "%c'%05d", (sign(val[1])), abs(val[1]));
    strcat(app, s);
    strcat(app, ".\n");

    strcpy(str, app);
}

void send_motor_ref(char* var){
    int ret = sendto(sockfd, (void*)var, 17, MSG_WAITALL, (sockaddr*)&server, len);
    if (ret == -1 || ret < 17){
        perror("send");
        exit(1);
    }
}
