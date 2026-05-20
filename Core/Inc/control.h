#ifndef INC_CONTROL_H_
#define INC_CONTROL_H_

#pragma once
#include <stdbool.h>

// Wall sensing
bool wallFront(void);
bool wallLeft(void);
bool wallRight(void);

// Motion
void moveForward_cell(void);
void turnRight_90(void);
void turnLeft_90(void);

#endif /* INC_CONTROL_H_ */
