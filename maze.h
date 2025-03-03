#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE 8

// Struktur für eine Zelle im Labyrinth
typedef struct {
    int walls[4]; // 0 = keine Wand, 1 = Wand (Index 0=N, 1=E, 2=S, 3=W)
} Cell;

extern Cell maze[MAZE_SIZE][MAZE_SIZE];

void initMaze();   
void setWall(int x, int y, int direction);  
void removeWall(int x, int y, int direction);
int hasWall(int x, int y, int direction);

#endif