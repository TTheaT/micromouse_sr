#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#include "main.h"

enum { MOTOR_LEFT = 1, MOTOR_RIGHT = 0 };
void motor_direction(int motor, char dir);
void motor_speed(int motor, uint16_t speed);
void motors_stop(void);

#endif /* INC_MOTORS_H_ */
