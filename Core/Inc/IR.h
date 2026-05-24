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

#define SR_SLOPE -9070.0f
#define SL_SLOPE -11804.0f
#define FR_SLOPE -13491.0f
#define FL_SLOPE -14617.0f

#define SR_INTERCEPT 3864.0f
#define SL_INTERCEPT 4002.0f
#define FR_INTERCEPT 3965.0f
#define FL_INTERCEPT 3949.0f

float measure_dist(dist_t dist);

#endif /* INC_IR_H_ */
