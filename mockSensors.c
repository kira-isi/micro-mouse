#include "mouse.h"
#include "maze.h"

static Cell realMaze[MAZE_SIZE][MAZE_SIZE];

void setMockMazeFromCurrent() {
    // 1. Kopiere den Zustand des vollen Labyrinths
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            for (int d = 0; d < 4; d++) {
                realMaze[x][y].walls[d] = maze[x][y].walls[d];
            }
        }
    }

    // 2. Setze das sichtbare Labyrinth zurück
    initMaze();
}

//hier ist der Mock der bisherigen scanSurroundings
void scanSurroundingsMock(Mouse* mouse) {
    int x = mouse->x;
    int y = mouse->y;

    if (realMaze[x][y].walls[0] && !hasWall(x, y, 0)) { setWall(x, y, 0); mazeUpdated = 1; }
    if (realMaze[x][y].walls[1] && !hasWall(x, y, 1)) { setWall(x, y, 1); mazeUpdated = 1; }
    if (realMaze[x][y].walls[2] && !hasWall(x, y, 2)) { setWall(x, y, 2); mazeUpdated = 1; }
    if (realMaze[x][y].walls[3] && !hasWall(x, y, 3)) { setWall(x, y, 3); mazeUpdated = 1; }
}