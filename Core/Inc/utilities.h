#ifndef INC_UTILITIES_H_
#define INC_UTILITIES_H_

#pragma once

#include "structures.h"
#include "queue.h"

//Maze Functions
void initMaze(Maze *maze);

//Utility Functions
Direction clockwiseStep(Direction currentDir);

Direction counterClockwiseStep(Direction currentDir);

void updateWalls(Maze* maze);

CellList getNeighborCells(Maze* maze, Coord c);

Cell getBestCell(Maze* maze);

void moveForward(Maze* maze);

void rotate(Maze* maze, Direction targetDir);

#endif /* INC_UTILITIES_H_ */
