#ifndef INC_STRUCTURES_H_
#define INC_STRUCTURES_H_

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "control.h"

#define MAZE_SIZE 16
#define MAX_COST 255

typedef enum {
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3
} Direction;

typedef enum {
    NORTH_MASK = 0x08,
    EAST_MASK  = 0x04,
    SOUTH_MASK = 0x02,
    WEST_MASK  = 0x01
} DirectionBitmask;

typedef struct {
    int x;
    int y;
} Coord;

typedef struct {
    Coord pos;
    Direction dir;
} Cell;

typedef struct {
    Cell cells[256];
    int head;
    int tail;
} Queue;

typedef struct {
    Coord mouse_pos;
    Direction mouse_dir;
    int distances[MAZE_SIZE][MAZE_SIZE];
    int cellWalls[MAZE_SIZE][MAZE_SIZE];
} Maze;

typedef struct {
    Cell cells[4];
    int size;
} CellList;

void initMaze(Maze* maze);

#endif /* INC_STRUCTURES_H_ */
