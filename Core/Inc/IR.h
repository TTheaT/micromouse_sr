#ifndef INC_IR_H_
#define INC_IR_H_
#include "main.h"

extern ADC_HandleTypeDef hadc1;

typedef enum{
	DIST_FL,
	DIST_FR,
	DIST_SL,
	DIST_SR
} dist_t;

#define SR_SLOPE -12620.0f
#define SL_SLOPE -2225.0f
#define FR_SLOPE -21610.0f
#define FL_SLOPE -16620.0f

#define SR_INTERCEPT 3971.0f
#define SL_INTERCEPT 3656.0f
#define FR_INTERCEPT 4253.0f
#define FL_INTERCEPT 4196.0f

float measure_dist(dist_t dist);

#endif /* INC_IR_H_ */
