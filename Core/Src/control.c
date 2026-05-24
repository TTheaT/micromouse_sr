#include "control.h"

int32_t current_dis = 0;
int32_t target_dis = 0;
//int32_t current_angle = 0;
//int32_t target_angle = 0;
int32_t dis_left_turn = 0;
int32_t dis_right_turn = 0;

// Wall sensing
bool wallFront(void) {
    float front_leftDis = measure_dist(DIST_FR);
    float front_rightDis = measure_dist(DIST_FL);
    float front_avg = (front_leftDis+front_rightDis)/2;
    return (front_avg < FRONT_THRESHOLD_M);
}

bool wallLeft(void) {
    float leftDis = measure_dist(DIST_SL);
//    float rightDis = measure_dist(DIST_SR);
    return (leftDis < LEFT_THRESHOLD_M);
}

bool wallRight(void) {
//    float leftDis = measure_dist(DIST_SL);
    float rightDis = measure_dist(DIST_SR);
    return (rightDis < RIGHT_THRESHOLD_M);
}

// Motion
void moveForward_cell(void) {
//	static int32_t avg_enc_count = (enc_left_count+enc_right_count)/2;

	current_dis = (enc_left_count+enc_right_count)/2;
	target_dis = TICKS_PER_CELL + current_dis;

	motor_direction(MOTOR_LEFT, 'F');
	motor_direction(MOTOR_RIGHT, 'F');

	set_target_speeds(RUN_SPEED, RUN_SPEED);

	//int32_t tick_count = encoder_avg_ticks();

	while (((enc_left_count+enc_right_count)/2) < target_dis) {
		//tick_count = encoder_avg_ticks();
		//avg_enc_count = (enc_left_count+enc_right_count)/2;
	}

	motors_stop();
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
//	HAL_Delay(500); //TAKE THIS AWAY IF FIGURE OUT A BETTER WAY
	//avg_enc_count=0;
}

//void turnRight_90(void) {
//
//	dis_left_turn = (((enc_left_count*M_PER_TICK)* 2 * PI * WHEEL_RADIUS_M) / 360);
//	dis_right_turn = (((enc_right_count*M_PER_TICK)* 2 * PI * WHEEL_RADIUS_M) / 360);
//	current_angle = ((dis_left_turn-dis_right_turn)/(2*RW))*(180/PI);
//	target_angle = 90;
//
//	motor_direction(MOTOR_LEFT, 'F');
//	motor_direction(MOTOR_RIGHT, 'B');
//
//	set_target_speeds(TURN_SPEED, TURN_SPEED);
//
//	while (((dis_left_turn-dis_right_turn)/(2*RW))*(180/PI) < target_angle) {
//			//tick_count = encoder_avg_ticks();
//			//avg_enc_count = (enc_left_count+enc_right_count)/2;
//	}
//	motors_stop();
//
//}

void turnRight_45(void) {
    int32_t start_left  = enc_left_count;
    int32_t start_right = enc_right_count;

    motor_direction(MOTOR_LEFT, 'F');
    motor_direction(MOTOR_RIGHT, 'B');
    set_target_speeds(TURN_SPEED, TURN_SPEED);

    float angle_deg = 0.0f;
    while (angle_deg < 93.0f) {
        float dist_left_m  = (enc_left_count  - start_left)  * M_PER_TICK;
        float dist_right_m = (enc_right_count - start_right) * M_PER_TICK;
        // For a right turn: left wheel goes forward (+), right goes backward (-)
        // So dist_left_m is positive and dist_right_m is negative,
        // and (dist_left_m - dist_right_m) is positive and growing.
        angle_deg = ((dist_left_m - dist_right_m) / (1.0f * RW)) * (180.0f / PI);
    }

    motors_stop();
}

void turnLeft_45(void) {
    int32_t start_left  = enc_left_count;
    int32_t start_right = enc_right_count;

    motor_direction(MOTOR_LEFT, 'B');
    motor_direction(MOTOR_RIGHT, 'F');
    set_target_speeds(TURN_SPEED, TURN_SPEED);

    float angle_deg = 0.0f;
    while (angle_deg < 93.0f) {
        float dist_left_m  = (enc_left_count  - start_left)  * M_PER_TICK;
        float dist_right_m = (enc_right_count - start_right) * M_PER_TICK;
        // For a left turn: left wheel goes backward (0), right goes forward (+)
        // So dist_right_m is positive and dist_left_m is negative,
        // and (dist_right_m - dist_left_m) is positive and growing.
        angle_deg = ((dist_right_m - dist_left_m) / (1.0f * RW)) * (180.0f / PI);
    }
    motors_stop();
}

void turnRight_90(void){
	turnRight_45();
	turnRight_45();
	HAL_Delay(500);
}

void turnLeft_90(void){
	turnLeft_45();
	turnLeft_45();
	HAL_Delay(500);
}


int16_t feedforward_pwm(float target_mps) {
    if (target_mps == 0.0f) return 0;   // don't apply deadband offset when commanding stop

    float pwm = FF_SLOPE *(target_mps) + FF_INTERCEPT;
    return (int16_t)pwm;
}
