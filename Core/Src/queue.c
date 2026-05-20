#include "queue.h"

//Queue Functions
void initQueue(Queue *q) { //Initialize empty queue
    q->head = 0;
    q->tail = 0;
}

bool isQEmpty(Queue *q) { //Return true if queue is empty, false otherwise
    return(q->head==q->tail);
}

void enqueue(Queue *q, Cell cell){ //Add a cell to the back of the queue
    q->cells[q->tail]=cell;
    q->tail++;
}

Cell dequeue(Queue *q){ //Remove and return the cell from the front
    Cell curCell = q->cells[q->head];
    q->head++;
    return(curCell);
}


