//##########################################################
//##                      R O B O T I S                   ##
//##          ReadWrite Example code for Dynamixel.       ##
//##                                           2009.11.10 ##
//##########################################################
#include <cstdio>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>

// Control table address
#define P_GOAL_POSITION_L	30
#define P_GOAL_POSITION_H	31
#define P_PRESENT_POSITION_L	36
#define P_PRESENT_POSITION_H	37
#define P_MOVING		46

#define P_GOAL_SPEED_L		32

// Defulat setting
#define DEFAULT_BAUDNUM		1 // 1Mbps
#define DEFAULT_ID		1


#include "servo_manager.hpp"

void PrintCommStatus(int CommStatus);
void PrintErrorCode(void);

int main()
{
	int baudnum = 1;
	int GoalPos[2] = {1, 1023};
	//int GoalPos[2] = {0, 4095}; // for Ex series
	int index = 0;
	int deviceIndex = 0; // USB ttyUSB0
	int Moving, PresentPos;
	int CommStatus;

	printf( "\n\nRead/Write example for Linux\n\n" );
	ServoManager sm;
	sm.hello_world();
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

	while(1)
	{
		printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
		if(getchar() == 0x1b)
			break;
		// Set goal speed
		dxl_write_word( BROADCAST_ID, P_GOAL_SPEED_L, 0 );
		// Write goal position
		dxl_write_word( BROADCAST_ID, P_GOAL_POSITION_L, GoalPos[index] );

		do
		{
			// Read present position
			PresentPos = dxl_read_word( BROADCAST_ID, P_PRESENT_POSITION_L );
			CommStatus = dxl_get_result();

			if( CommStatus == COMM_RXSUCCESS )
			{
				printf( "%d   %d\n",GoalPos[index], PresentPos );
				PrintErrorCode();
			}
			else
			{
				PrintCommStatus(CommStatus);
				break;
			}

			// Check moving done
			Moving = dxl_read_byte( BROADCAST_ID, P_MOVING );
			CommStatus = dxl_get_result();
			if( CommStatus == COMM_RXSUCCESS )
			{
				if( Moving == 0 )
				{
					// Change goal position
					if( index == 0 )
						index = 1;
					else
						index = 0;					
				}

				PrintErrorCode();
			}
			else
			{
				PrintCommStatus(CommStatus);
				break;
			}
		}while(Moving == 1);
		//dxl_ping( BROADCAST_ID );
		//if( dxl_get_result( ) == COMM_RXSUCCESS )
		//{
      		// Succeed to verify ID 2
      	//	printf("Success to verify ID%d\n", BROADCAST_ID);
		//}
	}

	// Close device
	dxl_terminate();
	printf( "Press Enter key to terminate...\n" );
	getchar();
	return 0;
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
