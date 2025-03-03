#include "maze.h"

// Das Labyrinth wird hier gespeichert
Cell maze[MAZE_SIZE][MAZE_SIZE];

// Initialisiert das Labyrinth mit leeren Wänden
void initMaze() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            for (int i = 0; i < 4; i++) {
                maze[x][y].walls[i] = 0;  // Alle Wände zuerst entfernen
            }
        }
    }

    // Außenwände setzen
    for (int x = 0; x < MAZE_SIZE; x++) {
        setWall(x, 0, 0);                // Obere Wand (Nord)
        setWall(x, MAZE_SIZE - 1, 2);    // Untere Wand (Süd)
    }
    for (int y = 0; y < MAZE_SIZE; y++) {
        setWall(0, y, 3);                // Linke Wand (West)
        setWall(MAZE_SIZE - 1, y, 1);    // Rechte Wand (Ost)
    }
}

// Setzt eine Wand in einer bestimmten Richtung
void setWall(int x, int y, int direction) {
    if (x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE) {
        maze[x][y].walls[direction] = 1;

        // Gegenüberliegende Wand der Nachbarzelle auch setzen
        switch (direction) {
            case 0: // Nord
                if (y > 0) maze[x][y - 1].walls[2] = 1;
                break;
            case 1: // Ost
                if (x < MAZE_SIZE - 1) maze[x + 1][y].walls[3] = 1;
                break;
            case 2: // Süd
                if (y < MAZE_SIZE - 1) maze[x][y + 1].walls[0] = 1;
                break;
            case 3: // West
                if (x > 0) maze[x - 1][y].walls[1] = 1;
                break;
        }
    }
}


// Entfernt eine Wand
void removeWall(int x, int y, int direction) {
    if (x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE) {
        maze[x][y].walls[direction] = 0;

        // Gegenüberliegende Wand der Nachbarzelle auch entfernen
        switch (direction) {
            case 0: // Nord
                if (y > 0) maze[x][y - 1].walls[2] = 0;
                break;
            case 1: // Ost
                if (x < MAZE_SIZE - 1) maze[x + 1][y].walls[3] = 0;
                break;
            case 2: // Süd
                if (y < MAZE_SIZE - 1) maze[x][y + 1].walls[0] = 0;
                break;
            case 3: // West
                if (x > 0) maze[x - 1][y].walls[1] = 0;
                break;
        }
    }
}

// Prüft, ob eine Wand existiert
int hasWall(int x, int y, int direction) {
    if (x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE) {
        return maze[x][y].walls[direction];
    }
    return 1; // Falls außerhalb des Labyrinths -> automatisch Wand
}