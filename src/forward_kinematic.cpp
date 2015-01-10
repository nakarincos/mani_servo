#include <cmath>
#define PI (3.14159265358979323846)
float INPUT_KINEMATIC_TABLE[4][4];
float REF_KINEMATIC_TABLE[4][4][4];
float GOAL_KINEMATIC_TABLE[4][4];
///// angle from Zi to Zi+1 measure about X /////
void input_alpha(){
	int i;
	float input;
	printf("===== Input Alpha =====\n");
	for(i = 0 ; i < 4 ; i++){
		printf("%d.)", i+1);
		scanf("%f", &input);
		INPUT_KINEMATIC_TABLE[0][i] = input;
	}
}
///// distance from Zi to Zi+1 measure along X /////
void input_a(){
	int i;
	float input;
	printf("===== Input A =====\n");
	for(i = 0 ; i < 4 ; i++){
		printf("%d.)", i+1);
		scanf("%f", &input);
		INPUT_KINEMATIC_TABLE[1][i] = input;
	}
}
///// distance from Xi-1 to Xi measure along Z /////
void input_d(){
	int i;
	float input;
	printf("===== Input D =====\n");
	for(i = 0 ; i < 4 ; i++){
		printf("%d.)", i+1);
		scanf("%f", &input);
		INPUT_KINEMATIC_TABLE[2][i] = input;
	}
}
///// angle from Xi-1 to Xi measure about Z /////
void input_theta(){
	int i;
	float input;
	printf("===== Input Theta =====\n");
	for(i = 0 ; i < 4 ; i++){
		printf("%d.)", i+1);
		scanf("%f", &input);
		INPUT_KINEMATIC_TABLE[3][i] = input;
	}
}
void reference_frame_calculator(int index){
	
	REF_KINEMATIC_TABLE[index][0][0] = cos(INPUT_KINEMATIC_TABLE[index][3]*PI/180);
	REF_KINEMATIC_TABLE[index][0][1] = (-1)*sin(INPUT_KINEMATIC_TABLE[index][3]*PI/180);
	REF_KINEMATIC_TABLE[index][0][2] = 0;
	REF_KINEMATIC_TABLE[index][0][3] = INPUT_KINEMATIC_TABLE[index][1];

	REF_KINEMATIC_TABLE[index][1][0] = sin(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180);
	REF_KINEMATIC_TABLE[index][1][1] = cos(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180);
	REF_KINEMATIC_TABLE[index][1][2] = (-1)*sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180);
	REF_KINEMATIC_TABLE[index][1][3] = (-1)*sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*INPUT_KINEMATIC_TABLE[index][2];

	REF_KINEMATIC_TABLE[index][2][0] = sin(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180);
	REF_KINEMATIC_TABLE[index][2][1] = cos(INPUT_KINEMATIC_TABLE[index][3]*PI/180) * sin(INPUT_KINEMATIC_TABLE[index][0]*PI/180);
	REF_KINEMATIC_TABLE[index][2][2] = cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180);
	REF_KINEMATIC_TABLE[index][2][3] = cos(INPUT_KINEMATIC_TABLE[index][0]*PI/180)*INPUT_KINEMATIC_TABLE[index][2];

	REF_KINEMATIC_TABLE[index][3][0] = 0;
	REF_KINEMATIC_TABLE[index][3][1] = 0;
	REF_KINEMATIC_TABLE[index][3][2] = 0;
	REF_KINEMATIC_TABLE[index][3][3] = 1;
}
void cross_matrix(){

}
void goal_calculator(int from, int end){
	from--;
	end--;
	GOAL_KINEMATIC_TABLE = REF_KINEMATIC_TABLE[from];
	if(from == end)
		return 0;
	for(int i = from+1 ; i <= end ; i++){

	}
}