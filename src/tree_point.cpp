#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;
#define PI (3.14159265358979323846)
float INPUT_KINEMATIC_TABLE[4][4];
float REF_KINEMATIC_TABLE[4][4][4];
float GOAL_KINEMATIC_TABLE[4][4];
///// angle from Zi to Zi+1 measure about X /////
void input_alpha(){
	for(int i = 0 ; i < 4 ; i++){
		INPUT_KINEMATIC_TABLE[i][0] = 0;
	}
}
///// distance from Zi to Zi+1 measure along X /////
void input_a(){
	INPUT_KINEMATIC_TABLE[0][1] = 0;
	INPUT_KINEMATIC_TABLE[1][1] = 50+(40/PI);
	INPUT_KINEMATIC_TABLE[2][1] = 40/PI;
	INPUT_KINEMATIC_TABLE[3][1] = 50;
}
///// distance from Xi-1 to Xi measure along Z /////
void input_d(){
	for(int i = 0 ; i < 4 ; i++){
		INPUT_KINEMATIC_TABLE[i][2] = 0;
	}
}


void reference_frame_calculator(int index){
	float tmp;
	REF_KINEMATIC_TABLE[index][0][0] = round(cos(INPUT_KINEMATIC_TABLE[index][3]*PI/180)*10000) / 10000;
	tmp = sin(INPUT_KINEMATIC_TABLE[index][3]*PI/180);
	REF_KINEMATIC_TABLE[index][0][1] = (tmp == 0 ? 0 : round((-1)*tmp*10000) / 10000);
	//REF_KINEMATIC_TABLE[index][0][1] = round((-1)*sin(INPUT_KINEMATIC_TABLE[index][3]*PI/180)*10000) / 10000;
	REF_KINEMATIC_TABLE[index][0][2] = 0;
	REF_KINEMATIC_TABLE[index][0][3] = round(INPUT_KINEMATIC_TABLE[index][1]*10000) / 10000;

	REF_KINEMATIC_TABLE[index][1][0] = round(sin(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*10000) / 10000;
	REF_KINEMATIC_TABLE[index][1][1] = round(cos(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*10000) / 10000;
	tmp = sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180);
	REF_KINEMATIC_TABLE[index][1][2] = (tmp == 0 ? 0 : round((-1)*tmp*10000) / 10000);
	// REF_KINEMATIC_TABLE[index][1][2] = round((-1)*sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*10000) / 10000;
	tmp = sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*INPUT_KINEMATIC_TABLE[index][2];
	REF_KINEMATIC_TABLE[index][1][3] = (tmp == 0 ? 0 : round((-1)*tmp*10000) / 10000);
	// REF_KINEMATIC_TABLE[index][1][3] = round((-1)*(sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*INPUT_KINEMATIC_TABLE[index][2]) *10000) / 10000;

	REF_KINEMATIC_TABLE[index][2][0] = round(sin(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*10000) / 10000;
	REF_KINEMATIC_TABLE[index][2][1] = round(cos(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*10000) / 10000;
	REF_KINEMATIC_TABLE[index][2][2] = round(cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*10000) / 10000;
	REF_KINEMATIC_TABLE[index][2][3] = round((cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*INPUT_KINEMATIC_TABLE[index][2])*10000) / 10000;

	REF_KINEMATIC_TABLE[index][3][0] = 0;
	REF_KINEMATIC_TABLE[index][3][1] = 0;
	REF_KINEMATIC_TABLE[index][3][2] = 0;
	REF_KINEMATIC_TABLE[index][3][3] = 1;

	// cout << "T" << index+1 << " : " << endl;
	// for(int i = 0 ; i < 4 ; i++){
	// 	for(int j = 0 ; j < 4 ; j++){
	// 		// if(REF_KINEMATIC_TABLE[i][j] == 0)
	// 		// 	cout << "Zero";
	// 		cout << REF_KINEMATIC_TABLE[index][i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << "***************************" << endl;

}
void cross_matrix(float a[][4], float b[][4]){
	float tmp_array[4][4];
	float sum = 0;
	for(int count = 0 ; count < 4 ; count++){
		
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 4 ; j++){
				sum += a[count][j] * b[j][i];
			}
			tmp_array[count][i] = sum;
			sum = 0;
		}
	}
	for(int i = 0 ; i < 4 ; i++){
		for(int j = 0 ; j < 4 ; j++){
			// cout << tmp_array[i][j] << " ";
			GOAL_KINEMATIC_TABLE[i][j] = tmp_array[i][j];
		}
		// cout << endl;
	}
	// cout << "========================" << endl;
}

void goal_calculator(int from, int end){
	from--;	
	end--;
	for(int i = 0 ; i < 4 ; i++){
		for(int j = 0 ; j < 4 ; j++){
			GOAL_KINEMATIC_TABLE[i][j] = REF_KINEMATIC_TABLE[from][i][j];
		}
	}
	if(from == end)
		return;
	for(int i = from+1 ; i <= end ; i++){
		cross_matrix(GOAL_KINEMATIC_TABLE, REF_KINEMATIC_TABLE[i]);
	}

}
float getX(){
	return GOAL_KINEMATIC_TABLE[0][3];
}
float getY(){
	return GOAL_KINEMATIC_TABLE[1][3];
}

void startTreePoint(){
	// ##############################################
	// ##        Initial Forward Kinematic         ##
	// ##############################################
	input_alpha();
	input_a();
	input_d();
	ofstream myfile("angle2.txt");
  	myfile << "=====================================\n";
  	myfile << "           Angle from tree           \n";
	myfile << "=====================================\n";
	for(int i = 0 ; i <= 360 ; i++){
		INPUT_KINEMATIC_TABLE[0][3] = 90;
		INPUT_KINEMATIC_TABLE[1][3] = i;
		INPUT_KINEMATIC_TABLE[2][3] = 0;
		INPUT_KINEMATIC_TABLE[3][3] = 0;
		for(int i = 0 ; i < 4 ; i++){
			reference_frame_calculator(i);
		}
		
		goal_calculator(1,4);
		cout << "Angle from tree => " << i << endl;
  		myfile << "Angle : " << i << "( "<< getX() <<" , "<< getY() <<" ) , ";
  		goal_calculator(1,3);
		cout << "Angle from tree => " << i << endl;
  		myfile << "( "<< getX() <<" , "<< getY() <<" )\n";

	}
	myfile.close();
}