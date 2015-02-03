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
	int i;
	float input;
	//printf("===== Input Alpha =====\n");
	for(i = 0 ; i < 4 ; i++){
		// printf("%d.)", i+1);
		// scanf("%f", &input);
		// INPUT_KINEMATIC_TABLE[i][0] = input;
		INPUT_KINEMATIC_TABLE[i][0] = 0;
	}
}
///// distance from Zi to Zi+1 measure along X /////
void input_a(){
	int i;
	float input;
	printf("===== Input A =====\n");
	INPUT_KINEMATIC_TABLE[0][1] = 0;
	// INPUT_KINEMATIC_TABLE[1][1] = 50+(40/PI);
	// INPUT_KINEMATIC_TABLE[2][1] = 40/PI;
	// INPUT_KINEMATIC_TABLE[3][1] = 0;
	for(i = 1 ; i < 4 ; i++){
		printf("%d.)", i+1);
		scanf("%f", &input);
		// INPUT_KINEMATIC_TABLE[i][1] = input;
		INPUT_KINEMATIC_TABLE[i][1] = 50;
	}
}
///// distance from Xi-1 to Xi measure along Z /////
void input_d(){
	int i;
	float input;
	// printf("===== Input D =====\n");
	for(i = 0 ; i < 4 ; i++){
		// printf("%d.)", i+1);
		// scanf("%f", &input);
		// INPUT_KINEMATIC_TABLE[i][2] = input;
		INPUT_KINEMATIC_TABLE[i][2] = 0;
	}
}
///// angle from Xi-1 to Xi measure about Z /////
// void input_theta(){
// 	int i;
// 	float input;
// 	printf("===== Input Theta =====\n");
// 	for(i = 0 ; i < 4 ; i++){
// 		printf("%d.)", i+1);
// 		scanf("%f", &input);
// 		INPUT_KINEMATIC_TABLE[i][3] = input;
// 	}
// }
void input_theta(int input, int i){
	// int i;
	// float input;
	// printf("===== Input Theta =====\n");
	// for(i = 0 ; i < 4 ; i++){
	// 	printf("%d.)", i+1);
	// 	scanf("%f", &input);
		INPUT_KINEMATIC_TABLE[i][3] = input;
	// }
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
	// cout << "from : " << from << " end : " << end << endl;
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
		// cout << "GOAL : "<< endl;
		// for(int k = 0 ; k < 4 ; k++){
		// 	for(int x = 0 ; x < 4 ; x++){
		// 		cout << GOAL_KINEMATIC_TABLE[k][x] << " ";
		// 	}
		// 	cout << endl;
		// }
		// cout << "REF : "<< endl;
		// for(int k = 0 ; k < 4 ; k++){
		// 	for(int x = 0 ; x < 4 ; x++){
		// 		cout << REF_KINEMATIC_TABLE[i][k][x] << " ";
		// 	}
		// 	cout << endl;
		// }
		// cout << "========================" << endl;
		cross_matrix(GOAL_KINEMATIC_TABLE, REF_KINEMATIC_TABLE[i]);
	}
	// cout << "FINAL POSITION : " << GOAL_KINEMATIC_TABLE[0][3] << " , " << GOAL_KINEMATIC_TABLE[1][3] << " , " << GOAL_KINEMATIC_TABLE[2][3] <<endl;
	//ofstream myfile("angle.txt");
	
	//myfile << "Angle : " << i;
	//myfile << "( " << GOAL_KINEMATIC_TABLE[0][3] << " , " << GOAL_KINEMATIC_TABLE[1][3] << " )\n";
  	//myfile.close();

}
float getX(){
	return GOAL_KINEMATIC_TABLE[0][3];
	// return GOAL_KINEMATIC_TABLE[0][2];
}

float getY(){
	return GOAL_KINEMATIC_TABLE[1][3];
	// return GOAL_KINEMATIC_TABLE[1][2];
}