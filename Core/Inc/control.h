#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#pragma once
#include <stdbool.h>

#define FF_SLOPE 995.0f
#define FF_INTERCEPT  900.0f

// Wall sensing
bool wallFront(void);
bool wallLeft(void);
bool wallRight(void);

// Motion
void moveForward_cell(void);
void turnRight_90(void);
void turnLeft_90(void);

int16_t feedforward_pwm(float target_mps);

#endif /* INC_CONTROL_H_ */
