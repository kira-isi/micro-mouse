#include "algorithms.h"

void runWallFollower(Mouse* mouse) {
    do {
        scanSurroundings(mouse); // Umgebung scannen und Wände aktualisieren
        
        // Bestimme die mögliche Bewegungsrichtung
        int rightDir = (mouse->dir + 1) % 4;
        int frontDir = mouse->dir;
        int leftDir = (mouse->dir + 3) % 4;

        int x = mouse->x;
        int y = mouse->y;

        // 1. Falls rechts frei ist, folge der rechten Wand
        if (!hasWall(x, y, rightDir)) {
            turnRight(mouse);
            moveForward(mouse);
            continue;
        }

        // 2. Falls geradeaus frei ist, gehe weiter
        if (!hasWall(x, y, frontDir)) {
            moveForward(mouse);
            continue;
        }

        // 3. Falls links frei ist, drehe nach links und gehe
        if (!hasWall(x, y, leftDir)) {
            turnLeft(mouse);
            moveForward(mouse);
            continue;
        }

        // 4. Falls alles blockiert ist, drehe um
        turnRight(mouse);
        turnRight(mouse);
        moveForward(mouse);

    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&  // Stoppe, wenn das Zentrum erreicht ist
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2 - 1) &&
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2 - 1));
}