#ifndef INC_ENCODERS_H_
#define INC_ENCODERS_H_
#include "main.h"

extern uint16_t enc_left;
extern uint16_t enc_right;
extern int32_t enc_left_count;
extern int32_t enc_right_count;
extern int32_t speed_left;
extern int32_t speed_right;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

void update_speed(void);

#endif /* INC_ENCODERS_H_ */
