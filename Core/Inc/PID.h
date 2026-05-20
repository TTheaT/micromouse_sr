#ifndef INC_PID_H_
#define INC_PID_H_

#include "main.h"

typedef struct {
    float kP;
    float kI;
    float kD;

    float error;
    float lastError;
    float integratedError;

    uint32_t lastTime;
} PID;

void pid_init(PID *pid, float kP, float kI, float kD);
float pid_calculate(PID *pid, float target, float current);

void set_target_speeds(float left, float right);

#endif /* INC_PID_H_ */
