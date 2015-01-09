//##########################################################
//##                      R O B O T I S                   ##
//##          ReadWrite Example code for Dynamixel.       ##
//##                                           2009.11.10 ##
//##########################################################
#include <cstdio>
#include <iostream>
#include <termio.h>
#include <unistd.h>
#include <math.h>
#include <dynamixel.h>
using namespace std;
// Control table address
#define P_GOAL_POSITION_L	30
#define P_GOAL_POSITION_H	31
#define P_SPEED_L	32
#define P_PRESENT_POSITION_L	36
#define P_PRESENT_POSITION_H	37
#define P_MOVING		46

// Defulat setting
#define DEFAULT_BAUDNUM		1 // 1Mbps
#define DEFAULT_ID		0

void PrintCommStatus(int CommStatus);
void PrintErrorCode(void);
void check_moving(int id, int pos);
int mode_select();
void mode1();
void mode2();
void mode3();
void resetId4();

int mode;
int speed;
int is_continue = 0;
int pos[4];

int main()
{
	int baudnum = 1;
	int GoalPos[2] = {0, 1023};
	//int GoalPos[2] = {0, 4095}; // for Ex series
	int index = 0;
	int deviceIndex = 0;
	int Moving, PresentPos;
	int CommStatus;
	//int id[4] = {1,11,18,20};
	
	printf( "\n\nRead/Write example for Linux\n\n" );
	///////// Open USB2Dynamixel ////////////
	if( dxl_initialize(deviceIndex, baudnum) == 0 )
	{
		printf( "Failed to open USB2Dynamixel!\n" );
		printf( "Press Enter key to terminate...\n" );
		getchar();
		return 0;
	}
	else
		printf( "Succeed to open USB2Dynamixel!\n" );

	
	while(1){
		if(!is_continue)
			mode = mode_select();
		if(mode == 1){
			mode1();
		}
		else if(mode == 2){
			mode2();
		}
		else if(mode == 3){
			mode3();
		}
		else
			break;

		cout << "Continue? (Y/N) >> ";
		char con;
		cin >> con;
		if(con == 'Y' || con == 'y')
			is_continue = 1;
		else
			is_continue = 0;
		
	}
	// Reset Servos


	// Close device
	dxl_terminate();
	printf( "Press Enter key to terminate...\n" );
	getchar();
	return 0;
}
int mode_select(){
	int input;
	cout << "================" << endl;
	cout << " Mode Selection" << endl;
	cout << "================" << endl;
	cout << "1.) 4 servos" << endl;
	cout << "2.) 2 servos >> ID 1,2" << endl;
	cout << "3.) 2 servos >> ID 3,4" << endl;
	cout << "Any key to Terminate" << endl;
	cout << "================" << endl;
	cout << "Mode : ";
	cin >> input;
	return input;
}
void mode1(){
	//while(1){
		// printf( "Mode 1!(press ESC and Enter to quit)\n" );
		// if(getchar() == 0x1b)
		// 	break;
		// Write goal position
		cout << "speed(0-1023) : ";
		cin >> speed;
		for(int i = 0 ; i < 4 ; i++){
			cout << "ID "<< i+1 << " position : ";
			cin >> pos[i];
		}
		resetId4();
		for(int i = 0 ; i < 4 ; i++){
			dxl_write_word( i+1, P_SPEED_L, speed);
			dxl_write_word( i+1, P_GOAL_POSITION_L, pos[i]);
			check_moving(i+1, pos[i]);
		}
	//}
}
void mode2(){
	//while(1){
		// printf( "Mode 2!(press ESC and Enter to quit)\n" );
		// if(getchar() == 0x1b)
		// 	break;
		// Write goal position
		cout << "speed(0-1023) : ";
		cin >> speed;
		cout << "ID 1 position(0 - 1023) : ";
		cin >> pos[0];
		cout << "ID 2 position(0- 1023) : ";
		cin >> pos[1];
		dxl_ping(4);
		if( dxl_get_result() == COMM_RXSUCCESS ){
			cout << "Ping Success!" << endl;
			resetId4();
		}
		else if( dxl_get_result() == COMM_RXTIMEOUT ){
			dxl_ping(4);
			if( dxl_get_result() == COMM_RXSUCCESS ){
				cout << "Ping Success!" << endl;
				resetId4();
			}
		}
		for(int i = 0 ; i < 2 ; i++){
			dxl_write_word( i+1, P_SPEED_L, speed);
			dxl_write_word( i+1, P_GOAL_POSITION_L, pos[i]);
			check_moving(i+1, pos[i]);
		}
	//}
}
void mode3(){
	//while(1){
		// Write goal position
		cout << "speed(0-1023) : ";
		cin >> speed;
		cout << "ID 3 position(0 - 1023) : ";
		cin >> pos[2];
		cout << "ID 4 position(200 - 800) : ";
		cin >> pos[3];
		for(int i = 2 ; i < 4 ; i++){
			resetId4();
			dxl_write_word( i+1, P_SPEED_L, speed);
			dxl_write_word( i+1, P_GOAL_POSITION_L, pos[i]);
			check_moving(i+1, pos[i]);
		}
	//}
}

void resetId4(){
	dxl_write_word( 4, P_GOAL_POSITION_L, 512);
	check_moving(4, 512);
}

void check_moving(int id, int pos){
	int curr_pos[10] = {dxl_read_word( id, P_PRESENT_POSITION_L )};
	int carry = 0;
	int carry_tmp = 0;
	while(1){
		int j;
		int curr = dxl_read_word( id, P_PRESENT_POSITION_L );
		int count = 0;
		for(j = 0 ; j < 10 ; j++){
			// printf("curr_pos %d : %d\n", j, curr_pos[j]);
			if(curr_pos[j] == curr)
				count++;
		}
		if(count == 10){
			if(abs(curr-pos) <= 3)
				break;
			// int tmp = pos - curr;
			// // cout << "tmp : " << tmp << endl;
			// dxl_write_word( id, P_GOAL_POSITION_L, curr+tmp);
			// carry_tmp++;
			// if(carry_tmp >= 3){
			// 	carry_tmp = 0;
			// 	carry++;
			// 	dxl_write_word( id, P_GOAL_POSITION_L, curr+tmp+carry);
			// }
		}
		else{
			for(j = 0 ; j < 10 ; j++){
				curr_pos[j] = dxl_read_word( id, P_PRESENT_POSITION_L );
			}
		}
		// printf(">> %d\n", curr);
		if(curr == pos)
			break;
	}
}


// Print communication result
void PrintCommStatus(int CommStatus)
{
	switch(CommStatus)
	{
	case COMM_TXFAIL:
		printf("COMM_TXFAIL: Failed transmit instruction packet!\n");
		break;

	case COMM_TXERROR:
		printf("COMM_TXERROR: Incorrect instruction packet!\n");
		break;

	case COMM_RXFAIL:
		printf("COMM_RXFAIL: Failed get status packet from device!\n");
		break;

	case COMM_RXWAITING:
		printf("COMM_RXWAITING: Now recieving status packet!\n");
		break;

	case COMM_RXTIMEOUT:
		printf("COMM_RXTIMEOUT: There is no status packet!\n");
		break;

	case COMM_RXCORRUPT:
		printf("COMM_RXCORRUPT: Incorrect status packet!\n");
		break;

	default:
		printf("This is unknown error code!\n");
		break;
	}
}

// Print error bit of status packet
void PrintErrorCode()
{
	if(dxl_get_rxpacket_error(ERRBIT_VOLTAGE) == 1)
		printf("Input voltage error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_ANGLE) == 1)
		printf("Angle limit error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_OVERHEAT) == 1)
		printf("Overheat error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_RANGE) == 1)
		printf("Out of range error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_CHECKSUM) == 1)
		printf("Checksum error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_OVERLOAD) == 1)
		printf("Overload error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_INSTRUCTION) == 1)
		printf("Instruction code error!\n");
}
