#include "PID.h"
extern float target_speed_left;
extern float target_speed_right;

void pid_init(PID *pid, float kP, float kI, float kD){
    pid->kP = kP;
    pid->kI = kI;
    pid->kD = kD;
    pid->error = 0;
    pid->lastError = 0;
    pid->integratedError = 0;
    pid->lastTime = HAL_GetTick();
}

float pid_calculate(PID *pid, float target, float current){
	pid->error = target - current;

	uint32_t currentTime = HAL_GetTick();
	float dt = (currentTime - pid->lastTime)/ 1000.0;

	if (dt <= 0) return 0;

	//P
	float p = pid->kP * pid->error;

	//I
	pid->integratedError += pid->error * dt;
	float i = pid->kI * pid->integratedError;
	float d = pid->kD * ((pid->error - pid->lastError)/dt);

	pid->lastError = pid->error;
	pid->lastTime = currentTime;

	return p + i + d;
}

void set_target_speeds(float left, float right) {
    target_speed_left = left;
    target_speed_right = right;
}
