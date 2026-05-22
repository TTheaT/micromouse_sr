#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "motors.h"
#include "IR.h"
#include "PID.h"
#include "encoders.h"
//
#define CELL_LENGTH_M 0.167f // standard micromouse cell
#define WHEEL_RADIUS_M 0.015f
#define TICKS_PER_WHEEL_REV 360.0f //12*30
#define M_PER_TICK  (2.0f * 3.14159265f * WHEEL_RADIUS_M / TICKS_PER_WHEEL_REV)
#define RUN_SPEED  0.4 // forward velocity setpoint
#define TURN_SPEED 0.35 // rotation speed
#define WHEEL_BASE  0.079  // distance between wheels (NEED TO MEASURE)
#define TICKS_PER_CELL (CELL_LENGTH_M/M_PER_TICK)

#define WALL_THRESHOLD_ADC 2000 //NEED TO TUNE
//both close = front wall; one close = side wall on that side
#define FRONT_BOTH_THRESHOLD 2500 // both must exceed for front (NEED TO TUNE)
#define SIDE_ONLY_THRESHOLD  2000 // one sensor exceeds = side wall (NEED TO TUNE)

//base speed slope and intercept
#define FF_SLOPE 995.0f
#define FF_INTERCEPT 890.0f

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern int32_t enc_left_count;
extern int32_t enc_right_count;

extern int32_t current;
extern int32_t target;

// Wall sensing
bool wallFront(void);
bool wallLeft(void);
bool wallRight(void);

// Motion
void moveForward_cell(void);
void turnRight_90(void);
void turnLeft_90(void);

// Encoder Calcs
//tic inline int32_t encoder_left_ticks(void) {
//   return (int32_t)__HAL_TIM_GET_COUNTER(&htim3);
//}
//
//static inline int32_t encoder_right_ticks(void) {
//   return (int32_t)__HAL_TIM_GET_COUNTER(&htim4);
//}
//
//static inline int32_t encoder_avg_ticks(void) {
//   return (encoder_left_ticks() + encoder_right_ticks()) / 2;
//}
//
//static inline int32_t encoder_diff_ticks(void) {
//   return encoder_left_ticks() - encoder_right_ticks();
//}

int16_t feedforward_pwm(float target_mps);



#endif /* INC_CONTROL_H_ */
