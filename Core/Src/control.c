#include "control.h"

int32_t current = 0;
int32_t target = 0;

// Wall sensing
bool wallFront(void) {
    uint16_t leftDis = measure_dist(DIST_FR);
    uint16_t rightDis = measure_dist(DIST_FL);
    return (leftDis > FRONT_BOTH_THRESHOLD) && (rightDis > FRONT_BOTH_THRESHOLD);
}

bool wallLeft(void) {
    uint16_t leftDis = measure_dist(DIST_FR);
    uint16_t rightDis = measure_dist(DIST_FL);
    return (leftDis > SIDE_ONLY_THRESHOLD) && (rightDis < SIDE_ONLY_THRESHOLD);
}

bool wallRight(void) {
    uint16_t leftDis = measure_dist(DIST_FR);
    uint16_t rightDis = measure_dist(DIST_FL);
    return (rightDis > SIDE_ONLY_THRESHOLD) && (leftDis < SIDE_ONLY_THRESHOLD);
}

// Motion
void moveForward_cell(void) {
//	static int32_t avg_enc_count = (enc_left_count+enc_right_count)/2;

	current = (enc_left_count+enc_right_count)/2;
	target = TICKS_PER_CELL;

	motor_direction(MOTOR_LEFT, 'F');
	motor_direction(MOTOR_RIGHT, 'F');

	set_target_speeds(RUN_SPEED, RUN_SPEED);

	//int32_t tick_count = encoder_avg_ticks();

	while (((enc_left_count+enc_right_count)/2) < target) {
		//tick_count = encoder_avg_ticks();
		//avg_enc_count = (enc_left_count+enc_right_count)/2;
	}

	motors_stop();
	//avg_enc_count=0;
}

void turnRight_90(void) {
	motor_direction(MOTOR_LEFT, 'F');
	motor_direction(MOTOR_RIGHT, 'B');
	set_target_speeds(TURN_SPEED, TURN_SPEED);

}

void turnLeft_90(void) {
	motor_direction(MOTOR_LEFT, 'B');
	motor_direction(MOTOR_RIGHT, 'F');
	set_target_speeds(TURN_SPEED, TURN_SPEED);
}

int16_t feedforward_pwm(float target_mps) {
    if (target_mps == 0.0f) return 0;   // don't apply deadband offset when commanding stop

    float pwm = FF_SLOPE *(target_mps) + FF_INTERCEPT;
    return (int16_t)pwm;
}
