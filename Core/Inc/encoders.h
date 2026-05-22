#ifndef INC_ENCODERS_H_
#define INC_ENCODERS_H_
#include "main.h"

extern uint16_t enc_left;
extern uint16_t enc_right;
extern int32_t enc_left_count;
extern int32_t enc_right_count;
extern int32_t speed_left;
extern int32_t speed_right;
extern float speed_left_mps;
extern float speed_right_mps;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

#define WHEEL_RADIUS_M 0.015f
#define TICKS_PER_WHEEL_REV 360.0f //12*30
#define SAMPLE_MS 35
#define M_PER_TICK  (2.0f * 3.14159265f * WHEEL_RADIUS_M / TICKS_PER_WHEEL_REV)
#define MS_PER_SEC  1000
#define SPEED_MULT  (MS_PER_SEC / SAMPLE_MS)

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);


void update_speed(void);

//int32_t encoder_update(void);

#endif /* INC_ENCODERS_H_ */
