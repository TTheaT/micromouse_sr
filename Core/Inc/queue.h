#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#pragma once
#include "structures.h"

//Queue Functions
void initQueue(Queue *q);

bool isQEmpty(Queue *q);

void enqueue(Queue *q, Cell cell);

Cell dequeue(Queue *q);

#endif /* INC_QUEUE_H_ */
