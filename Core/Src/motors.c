#include "motors.h"

extern TIM_HandleTypeDef htim2;

void motor_direction(int motor, char dir){
	if(motor == MOTOR_RIGHT){
		switch(dir){ //F=forward, B=Backward
		   case 'F':
			   HAL_GPIO_WritePin(MR_FWD_GPIO_Port, MR_FWD_Pin, GPIO_PIN_RESET);
			   HAL_GPIO_WritePin(MR_BWD_GPIO_Port, MR_BWD_Pin, GPIO_PIN_SET);
			   break;
		   case 'B':
			   HAL_GPIO_WritePin(MR_FWD_GPIO_Port, MR_FWD_Pin, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(MR_BWD_GPIO_Port, MR_BWD_Pin, GPIO_PIN_RESET);
		}
	}
	else{ //MOTOR_LEFT
		switch(dir){
		   case 'F':
			   HAL_GPIO_WritePin(ML_FWD_GPIO_Port, ML_FWD_Pin, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(ML_BWD_GPIO_Port, ML_BWD_Pin, GPIO_PIN_RESET);
		       break;
		   case 'B':
			   HAL_GPIO_WritePin(ML_FWD_GPIO_Port, ML_FWD_Pin, GPIO_PIN_RESET);
			   HAL_GPIO_WritePin(ML_BWD_GPIO_Port, ML_BWD_Pin, GPIO_PIN_SET);
			   break;
		}
	}
}

void motor_speed(int motor, uint16_t speed){
    if (motor == MOTOR_RIGHT){
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, speed);
    }
    else{
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, speed);
    }
}

void motors_stop(void){
    motor_speed(MOTOR_LEFT, 0);
    motor_speed(MOTOR_RIGHT, 0);

    HAL_GPIO_WritePin(ML_FWD_GPIO_Port, ML_FWD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ML_BWD_GPIO_Port, ML_BWD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MR_FWD_GPIO_Port, MR_FWD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MR_BWD_GPIO_Port, MR_BWD_Pin, GPIO_PIN_RESET);
}

