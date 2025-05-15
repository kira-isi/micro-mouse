#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../maze.h"
#include "../mouse.h"
#include "../utils/stack.h"
#include "../utils/queue.h"

void runDijkstra(Mouse* mouse);
void runAstar(Mouse* mouse);
void runWallFollower(Mouse* mouse);
void runDFS_Target(Mouse* mouse);
void runDFS_Explore(Mouse* mouse);
void runFloodFill(Mouse* mouse);
void runModifiedFloodFill(Mouse* mouse);
void runBellmanFord(Mouse* mouse);

// Gemeinsames
typedef struct {
    int x;
    int y;
} Coordinates;
#define MAX_COST 255
extern int cost[MAZE_SIZE][MAZE_SIZE];
extern Coordinates previous[MAZE_SIZE][MAZE_SIZE];
void printCostMatrix();
void moveToLowestCost(Mouse* mouse);
void setGoal();
void turnToDirection(Mouse* mouse, int targetDir);
int countOpenPaths(int x, int y);
void getNextPosition(int *x, int *y, int dir);
int getDirectionToTarget(Mouse* mouse, int targetX, int targetY);
void reconstructPath(Stack* stack, int goalX, int goalY);
void performBacktracking(Mouse* mouse);
void setCostMatrixMax();
void setCostMatrixGoals(Queue* queue);

#endif