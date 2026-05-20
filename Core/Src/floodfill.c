#include "floodfill.h"

//Floodfill Function
void floodFill(Maze* maze, Coord* goals, int numGoals){ //Function to be called everytime you move into a new cell
    //Create and initialize the queue
    Queue q;
    initQueue(&q);

    //Reset all distance to MAX_COST
    for(int y = 0; y < MAZE_SIZE; y++){
        for(int x = 0; x < MAZE_SIZE; x++) {
            maze->distances[y][x] = MAX_COST;
        }
    }

    //Enqueue all goal cells and set their distance to 0
    for(int i = 0; i < numGoals; i++){
        Coord goal = goals[i];
        maze->distances[goal.y][goal.x] = 0;

        Cell goalCell;
        goalCell.pos = goal;
        goalCell.dir = NORTH;
        enqueue(&q, goalCell);
    }

    //Iteration of the queue
    while(!isQEmpty(&q)){
        Cell currentCell = dequeue(&q); //Dequeue the front cell
        int currentDist = maze->distances[currentCell.pos.y][currentCell.pos.x];//Get the current cell's distance value
        int newDist = currentDist+1;
        CellList neighbors = getNeighborCells(maze, currentCell.pos);//Get all accessible neighbors
        for(int i = 0; i < neighbors.size; i++){
            Cell neighbor = neighbors.cells[i];
            if(maze->distances[neighbor.pos.y][neighbor.pos.x] > newDist){ //Check if neighbor's current distance is worse than new path
                maze->distances[neighbor.pos.y][neighbor.pos.x] = newDist; //Update to better distance
                enqueue(&q, neighbor);//Add neighbor to queue so that we can chech neighbor later
            }
        }

    }

}


