#include "encoders.h"

uint16_t enc_left = 0;
uint16_t enc_right = 0;
int32_t enc_left_count = 0;
int32_t enc_right_count = 0;
uint16_t cell_tick_count_left = 0;
uint16_t cell_tick_count_right = 0;

int32_t speed_left = 0;
int32_t speed_right = 0;
float speed_left_mps = 0;
float speed_right_mps = 0;

static uint16_t prev_left = 0;
static uint16_t prev_right = 0;
static int32_t old_left_count = 0;
static int32_t old_right_count = 0;


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        enc_left = __HAL_TIM_GET_COUNTER(htim);
        int16_t delta = (int16_t)(enc_left - prev_left); // handles wrap
        enc_left_count += delta;
        prev_left = enc_left;
    }
    if (htim->Instance == TIM4) {
        enc_right = __HAL_TIM_GET_COUNTER(htim);
        int16_t delta = (int16_t)(enc_right - prev_right);
        enc_right_count += delta;
        prev_right = enc_right;
    }
}


void update_speed(void) {
    speed_left = (enc_left_count - old_left_count)*SPEED_MULT;
    speed_right = (enc_right_count - old_right_count)*SPEED_MULT;
    speed_left_mps = speed_left * M_PER_TICK;
    speed_right_mps = speed_right * M_PER_TICK;
    old_left_count = enc_left_count;
    old_right_count = enc_right_count;
}

//int32_t encoder_update(void){
//	cell_tick_count_left = __HAL_TIM_GET_COUNTER(htim);
//	cell_tick_count_right = __HAL_TIM_GET_COUNTER(htim);
//}

