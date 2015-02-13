#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include <forward_kinematic.cpp>
using namespace std;
#define PI (3.14159265358979323846)
// float INPUT_KINEMATIC_TABLE[4][4];
// float REF_KINEMATIC_TABLE[4][4][4];
// float GOAL_KINEMATIC_TABLE[4][4];
///// angle from Zi to Zi+1 measure about X /////
typedef struct Range{
	float a,b;
};
float goalX, goalY;
float answer_Angle[3] = {0};
Range limit_angle[3];
void setTarget(float x, float y){
	goalX = x;
	goalY = y;
	if(goalX >= 0){
		limit_angle[0].a = -90;
		limit_angle[0].b = 30;
		limit_angle[1].a = 30;
		limit_angle[1].b = 180;
		limit_angle[2].a = 0;
		limit_angle[2].b = 150;
	}
	else{
		limit_angle[0].a = -210;
		limit_angle[0].b = -90;
		limit_angle[1].a = -180;
		limit_angle[1].b = -30;
		limit_angle[2].a = -150;
		limit_angle[2].b = 0;
	}
}
void findAngle(){
	// for(int i = limit_angle[0].a ; i <= limit_angle[0].b ; i++){
	// 	for(int j = limit_angle[1].a ; j <= limit_angle[1].b ; j++){
	// 		for(int k = limit_angle[2].a ; k <= limit_angle[2].b ; k++){
	// 			cout << k << " ";
	// 		}
	// 		cout << j << endl;
	// 	}
	// 	cout << i << " ============================" <<endl;
	// }
	int i = limit_angle[0].a;
	int j = limit_angle[1].a;
	int k = limit_angle[2].a;
	int counteri = 10;
	int counterj = 10;
	int counterk = 10;
	input_alpha();
	input_a();
	input_d();
	float x,y;
	float diff = 100, tmp;
	Range answer;

	ofstream myfile("test.txt");
	myfile << "=====================================\n";
  	myfile << "             Point Moving            \n";
	myfile << "=====================================\n";
	// while(i <= limit_angle[0].b){
	// 	j = limit_angle[1].a;
	// 	while(j <= limit_angle[1].b){
	// 		k = limit_angle[2].a;
	// 		while(k <= limit_angle[2].b){
	// 			input_theta(i, 0);
	// 			input_theta(j, 1);
	// 			input_theta(k, 2);
	// 			input_theta(0, 3);
	// 			for(int i = 0 ; i < 4 ; i++){
	// 				reference_frame_calculator(i);
	// 			}
	// 			goal_calculator(1,4);
	// 			//myfile << "ID1: " << i << " ID2: " << j << " ID3: " << k << " ( " << getX() << " , " << getY() << " )\n\n";
	// 			x = getX();
	// 			y = getY();
	// 			if(x <= goalX+1 && x >= goalX-1){
	// 				counterk = 1;
	// 				// myfile << "===== CRITICAL1 =====\n";
	// 				if(y <= goalY+1 && y >= goalY-1){
	// 					myfile << "=================\n";
	// 					myfile << "ID1: " << i << " ID2: " << j << " ID3: " << k << " ( " << getX() << " , " << getY() << " )\n";
	// 					myfile << "DIFF X: " << x-goalX << " ,Y: " << y-goalY << " \n";
	// 					tmp = abs(x-goalX) + abs(y-goalY);
	// 					myfile << "SUM DIFF =  " << tmp << " \n\n";
	// 					if(diff > tmp){
	// 						diff = tmp;
	// 						answer.a = x;
	// 						answer.b = y;
	// 						answer_Angle[0] = i;
	// 						answer_Angle[1] = j;
	// 						answer_Angle[2] = k;
	// 					}
	// 				}
	// 			}
	// 			else{
	// 				counterk = 10;
	// 			}
	// 			k += counterk;
	// 		}
	// 		if(x <= goalX+5 && x >= goalX-5){
	// 			counterj = 1;
	// 			// myfile << "===== CRITICAL2 =====\n";
	// 		}
	// 		else{
	// 			counterj = 10;
	// 		}
	// 		j += counterj;
	// 	}
	// 	if(x <= goalX+5 && x >= goalX-5){
	// 		counteri = 1;
	// 		// myfile << "===== CRITICAL3 =====\n";
	// 	}
	// 	else{
	// 		counteri = 10;
	// 	}
	// 	i += counteri;
	// }
	///////////////////////////////////////////////////////////////
	int is_ok = 0;
	while(i <= limit_angle[0].b){
		j = limit_angle[1].a;
		while(j <= limit_angle[1].b){
			// k = limit_angle[2].a;
			// while(k <= limit_angle[2].b){
				input_theta(i, 0);
				input_theta(j, 1);
				input_theta(0, 2);
				input_theta(0, 3);
				for(int i = 0 ; i < 4 ; i++){
					reference_frame_calculator(i);
				}
				goal_calculator(1,3);
				//myfile << "ID1: " << i << " ID2: " << j << " ID3: " << k << " ( " << getX() << " , " << getY() << " )\n\n";
				x = getX();
				y = getY();
				if(x <= goalX+1 && x >= goalX-1){
					// counterk = 1;
					// myfile << "===== CRITICAL1 =====\n";
					if(y <= goalY+1 && y >= goalY-1){
						myfile << "=================\n";
						myfile << "ID1: " << i << " ID2: " << j << " ( " << getX() << " , " << getY() << " )\n";
						myfile << "DIFF X: " << x-goalX << " ,Y: " << y-goalY << " \n";
						tmp = abs(x-goalX) + abs(y-goalY);
						myfile << "SUM DIFF =  " << tmp << " \n\n";
						if(diff > tmp){
							diff = tmp;
							answer.a = x;
							answer.b = y;
							answer_Angle[0] = i;
							answer_Angle[1] = j;
							// answer_Angle[2] = k;
						}
					}
				}
				// else{
					// counterk = 10;
				// }
				// k += counterk;
			// }
			if(x <= goalX+5 && x >= goalX-5){
				counterj = 1;
				// myfile << "===== CRITICAL2 =====\n";
			}
			else{
				counterj = 10;
			}
			j += counterj;
		}
		if(x <= goalX+5 && x >= goalX-5){
			counteri = 1;
			is_ok = 1;
			// myfile << "===== CRITICAL3 =====\n";
		}
		else{
			if(!is_ok)
				counteri = 10;
			else
				counteri = limit_angle[0].b;
		}
		i += counteri;
	}

	myfile << "=====   ANSWER   =====\n";
	myfile << "DIFF: " << diff <<"\n";
	myfile << "X: " << answer.a << " , Y: " << answer.b << "\n";
	myfile << "ID1: " << answer_Angle[0] << " , ID2: " << answer_Angle[1] << "\n";
	myfile.close();

}

int getID1(){
	float converter = 1024/300;
	if(answer_Angle[0] >= 0 && answer_Angle[0] <= 60){
		return (int)((240+answer_Angle[0])*converter);
	}
	else if(answer_Angle[0] <= 0 && answer_Angle[0] >= -240){
		return (int)(((240-answer_Angle[0]))*converter);
	}
}
int getID2(){
	float converter = 1024/300;
	if(answer_Angle[1] >= 30 && answer_Angle[1] <= 180){
		return (int)((answer_Angle[1]-30)*converter);
	}
	else if(answer_Angle[1] <= -30 && answer_Angle[1] >= -180){
		return (int)(((330+answer_Angle[1]))*converter);
	}
}
int getID3(){
	float converter = 1024/300;
	if(answer_Angle[2] >= 0 && answer_Angle[2] <= 150){
		return (int)((150+answer_Angle[2])*converter);
	}
	else if(answer_Angle[2] <= 0 && answer_Angle[2] >= -150){
		return (int)(((0-answer_Angle[2]))*converter);
	}
}