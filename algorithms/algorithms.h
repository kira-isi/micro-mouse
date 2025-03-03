#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../maze.h"
#include "../mouse.h"

void runDijkstra();
void runAstar();
void runWallFollower(Mouse* mouse);
void runDfs();
void runFloodFill(Mouse* mouse);
void runModifiedFloodFill();
void runBellmanFord();

// Gemeinsames für Flood-Fill und Modified Flood-Fill
#define MAX_COST 255
extern int cost[MAZE_SIZE][MAZE_SIZE];
void printCostMatrix();
void moveToLowestCost(Mouse* mouse);
void setGoal();

#endif