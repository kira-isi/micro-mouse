#include "algorithms.h"
#include "..\utils\stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack stack;

void performBacktracking(Mouse* mouse) {
    while (!isStackEmpty(&stack)) {
        int prevX, prevY;
        pop(&stack, &prevX, &prevY);
        //printf("Backtracking von (%d, %d) nach (%d, %d)\n", mouse->x, mouse->y, prevX, prevY);

        // **Setze das aktuelle Feld als vollständig erkundet**
        cost[mouse->x][mouse->y] = 2;

        // **Drehe zur richtigen Richtung zurück**
        int backDir = getDirectionToTarget(mouse, prevX, prevY);
        turnToDirection(mouse, backDir);

        // **Falls vor uns ein unerforschter Pfad (`1`) ist, stoppe das Backtracking hier**
        int nx = mouse->x, ny = mouse->y;
        getNextPosition(&nx, &ny, mouse->dir);
        if (cost[nx][ny] == 1) {
            moveForward(mouse);
            return;  // **Backtracking beendet – `runDFS()` übernimmt**
        }

        // **Falls kein neuer Weg vor uns ist, weiter zurückgehen**
        moveForward(mouse);
    }

    // **Falls der Stack leer ist, Notfall-Stopp**
    printf("Fehler: Stack ist leer, aber Backtracking nötig! Notfall-Stopp.\n");
    exit(1);
}


void runDFS_Target(Mouse* mouse) {
    initStack(&stack);

    // **Setze das Startfeld als besucht und in den Stack**
    cost[mouse->x][mouse->y] = 1;
    push(&stack, mouse->x, mouse->y);

    do {
        scanSurroundings(mouse);

        int moved = 0;
        int nx, ny;

        // **Prüfe, ob das aktuelle Feld eine Ecke oder ein Tunnel ist**
        if (countOpenPaths(mouse->x, mouse->y) == 2 && !(mouse->x == 0 && mouse->y == 0)) {  
            cost[mouse->x][mouse->y] = 2;  // Sofort als vollständig erkundet markieren
        }

        // Normale Bewegung
        for (int i = 0; i < 3; i++) {  // Prüfreihenfolge: Links, Geradeaus, Rechts
            int checkDir;
            if (i == 0) checkDir = (mouse->dir + 3) % 4;  // Links
            else if (i == 1) checkDir = mouse->dir;       // Geradeaus
            else checkDir = (mouse->dir + 1) % 4;         // Rechts

            if (!hasWall(mouse->x, mouse->y, checkDir)) {
                nx = mouse->x, ny = mouse->y;
                getNextPosition(&nx, &ny, checkDir);
                if (cost[nx][ny] == 0) {  
                    if (i == 0) turnLeft(mouse);
                    else if (i == 2) turnRight(mouse);
                    moveForward(mouse);
                    cost[mouse->x][mouse->y] = 1;  // Markiere als besucht
                    push(&stack, mouse->x, mouse->y);
                    moved = 1;
                    break;
                }
            }
        }

        // falls unbekannter Weg endet -> Backtracking
        if (!moved) {
            printf("Bachtrackin!\n");
            performBacktracking(mouse);
        }

        printCostMatrix(); //zum Testen

    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == (MAZE_SIZE / 2) - 1) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == (MAZE_SIZE / 2) - 1));
}