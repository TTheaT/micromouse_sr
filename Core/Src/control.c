#include "control.h"
#include "main.h"
#include "motors.h"
#include "IR.h"
#include "PID.h"

// Constants (placeholder rn)
#define CELL_LENGTH_MM 180 // standard micromouse cell
#define RUN_SPEED  300 // forward velocity setpoint
#define TURN_SPEED 200 // rotation speed
#define WHEEL_BASE  80  // distance between wheels (NEED TO MEASURE)

#define MS_PER_CELL ((CELL_LENGTH_MM * 1000)/RUN_SPEED_MMS)
// For a 90 degree turn: arc length = (pi/2) * (wheelBase/2) per wheel
// = ~63mm at 80mm wheelbase. At 200mm/s that's ~315ms (NEED TO MEASURE)
#define MS_PER_90_TURN 350

#define WALL_THRESHOLD_ADC 2000 // NEED TO TUNE
//both close = front wall; one close = side wall on that side
#define FRONT_BOTH_THRESHOLD 2500 // both must exceed for front (NEED TO TUNE)
#define SIDE_ONLY_THRESHOLD  2000 // one sensor exceeds = side wall (NEED TO TUNE)

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
	motor_direction(MOTOR_LEFT, 'F');
	motor_direction(MOTOR_RIGHT, 'F');
	set_target_speed(RUN_SPEED, RUN_SPEED);

}

void turnRight_90(void) {
	motor_direction(MOTOR_LEFT, 'F');
	motor_direction(MOTOR_RIGHT, 'B');
	set_target_speed(TURN_SPEED, TURN_SPEED);

}

void turnLeft_90(void) {
	motor_direction(MOTOR_LEFT, 'B');
	motor_direction(MOTOR_RIGHT, 'F');
	set_target_speed(TURN_SPEED, TURN_SPEED);
}
