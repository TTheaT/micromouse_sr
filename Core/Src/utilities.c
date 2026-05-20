#include "utilities.h"
#include "control.h"

void initMaze(Maze *maze){
    //initialize all walls to 0
    for(int y=0; y < MAZE_SIZE; y++){
        for(int x=0; x < MAZE_SIZE; x++){
            maze->cellWalls[y][x] = 0;
        }
    }

    maze->mouse_pos.x = 0;
    maze->mouse_pos.y = 0;

    maze->mouse_dir = NORTH;
}

Direction clockwiseStep(Direction currentDir){ //returns the direction after turning 90° clockwise
    return (Direction)((currentDir+1)%4); //plus 1 and wrap around using modulo
}

Direction counterClockwiseStep(Direction currentDir){ //returns the direction after turning 90° counterclockwise
    return (Direction)((currentDir+3)%4);
}

void updateWalls(Maze* maze){
    int x = maze->mouse_pos.x;
    int y = maze->mouse_pos.y;
    Direction dir = maze->mouse_dir;

    //check for front wall and update BOTH SIDES
    int masks[4] = {NORTH_MASK, EAST_MASK, SOUTH_MASK, WEST_MASK};
    //offset arrays for neighbor cell positions
    int dx[] = {0, 1, 0, -1};  // NORTH, EAST, SOUTH, WEST
    int dy[] = {1, 0, -1, 0};

    if (wallFront()){
        maze->cellWalls[y][x] |= masks[dir];
        if(y+dy[dir] >= 0 && y+dy[dir] < MAZE_SIZE && x+dx[dir] >=0 && x+dx[dir] < MAZE_SIZE)
        maze->cellWalls[y+dy[dir]][x+dx[dir]] |= masks[(dir+2)%4]; //set wall on the opposite side
    }

    if (wallLeft()){
        maze->cellWalls[y][x] |= masks[(dir+3)%4];
        if(y+dy[dir] >= 0 && y+dy[dir] < MAZE_SIZE && x+dx[dir] >=0 && x+dx[dir] < MAZE_SIZE)
        maze->cellWalls[y+dy[(dir+3)%4]][x+dx[(dir+3)%4]] |= masks[(dir+1)%4];
    }

    if (wallRight()){
        maze->cellWalls[y][x] |= masks[(dir+1)%4];
        if(y+dy[dir] >= 0 && y+dy[dir] < MAZE_SIZE && x+dx[dir] >=0 && x+dx[dir] < MAZE_SIZE)
        maze->cellWalls[y+dy[(dir+1)%4]][x+dx[(dir+1)%4]] |= masks[(dir+3)%4];
    }
}

CellList getNeighborCells(Maze* maze, Coord c){ //return all neighboring cells not blocked by walls
    CellList neighbors;
    neighbors.size = 0;

    Cell neighbor;

    //check north: y+1
    if (c.y + 1 < MAZE_SIZE){
        //if there's no north wall in current cell, add north neighbor
        if (!(maze->cellWalls[c.y][c.x] & NORTH_MASK)){
            neighbor.pos.x = c.x;
            neighbor.pos.y = c.y + 1;
            neighbor.dir = NORTH;
            neighbors.cells[neighbors.size++] = neighbor;
        }
    }

    //check east: x+1
    if (c.x + 1 < MAZE_SIZE){
        if (!(maze->cellWalls[c.y][c.x] & EAST_MASK)) {
            neighbor.pos.x = c.x + 1;
            neighbor.pos.y = c.y;
            neighbor.dir = EAST;
            neighbors.cells[neighbors.size++] = neighbor;
        }
    }

    //check south: y-1
    if (c.y - 1 >= 0){
        if (!(maze->cellWalls[c.y][c.x] & SOUTH_MASK)) {
            neighbor.pos.x = c.x;
            neighbor.pos.y = c.y - 1;
            neighbor.dir = SOUTH;
            neighbors.cells[neighbors.size++] = neighbor;
        }
    }

    //check west: x-1
    if (c.x - 1 >= 0){
        if (!(maze->cellWalls[c.y][c.x] & WEST_MASK)) {
            neighbor.pos.x = c.x - 1;
            neighbor.pos.y = c.y;
            neighbor.dir = WEST;
            neighbors.cells[neighbors.size++] = neighbor;
        }
    }

    return neighbors;
}

Cell getBestCell(Maze* maze){
    //get current position
    Coord currentPos = maze->mouse_pos;

    //get all accessible neighbors
    CellList neighbors = getNeighborCells(maze, currentPos);

    //find neighbor with lowest distance
    Cell bestCell;
    int lowestDistance = MAX_COST+1;

    for (int i = 0; i < neighbors.size; i++){
        Cell neighbor = neighbors.cells[i];
        int neighborDistance = maze->distances[neighbor.pos.y][neighbor.pos.x];

        if (neighborDistance < lowestDistance) {
            lowestDistance = neighborDistance;
            bestCell = neighbor;
        }
    }
    return bestCell;
}

void moveForward(Maze* maze){
	moveForward_cell();

    if(maze->mouse_dir == NORTH){
        maze->mouse_pos.y++;
    }
    else if(maze->mouse_dir == EAST){
        maze->mouse_pos.x++;
    }
    else if(maze->mouse_dir == SOUTH){
        maze->mouse_pos.y--;
    }
    else if(maze->mouse_dir == WEST){
        maze->mouse_pos.x--;
    }
}

void rotate(Maze* maze, Direction targetDir){
    int currentDir = (int)maze->mouse_dir;
    int target = (int)targetDir;
    int diff = (target - currentDir + 4) % 4;

    if (diff == 0){
        return;
    }
    else if (diff == 1){
        turnRight_90();
        maze->mouse_dir = clockwiseStep(maze->mouse_dir);
    }
    else if (diff == 2){
        turnRight_90();
        turnRight_90();
        maze->mouse_dir = clockwiseStep(clockwiseStep(maze->mouse_dir));
    }
    else if (diff == 3){
        turnLeft_90();
        maze->mouse_dir = counterClockwiseStep(maze->mouse_dir);
    }
}
