#ifndef MOUSE_H
#define MOUSE_H

#include "maze.h"

typedef struct {
    int x;    // X-Koordinate der Maus
    int y;    // Y-Koordinate der Maus
    int dir;  // Richtung: 0 = Norden, 1 = Osten, 2 = Süden, 3 = Westen
} Mouse;

extern int mazeUpdated; // Wird auf 1 gesetzt, wenn sich das Labyrinth verändert

// Funktionen zur Steuerung der Maus
void initMouse(Mouse* mouse);
void moveForward(Mouse* mouse);
void turnLeft(Mouse* mouse);
void turnRight(Mouse* mouse);
void scanSurroundings(Mouse* mouse);
int isWall(Mouse* mouse);
int detectWallSensor(int direction);

#endif