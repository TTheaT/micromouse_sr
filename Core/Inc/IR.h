#ifndef INC_IR_H_
#define INC_IR_H_
#include "main.h"

extern ADC_HandleTypeDef hadc1;

typedef enum{
	DIST_FL,
	DIST_FR
} dist_t;

uint16_t measure_dist(dist_t dist);

#endif /* INC_IR_H_ */
