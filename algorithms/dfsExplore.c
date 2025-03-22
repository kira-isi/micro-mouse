#include "algorithms.h"
#include "..\utils\stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack stack;

int labyrinthErforscht() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (cost[x][y] == 0) {
                return 1;  // Es gibt noch unerforschte Felder
            }
        }
    }
    return 0;  // Alle Felder wurden erforscht
}


void runDFS_Explore(Mouse* mouse) {
    initStack(&stack);

    // **Setze das Startfeld als besucht und in den Stack**
    cost[mouse->x][mouse->y] = 1;
    push(&stack, mouse->x, mouse->y);

    do {
        scanSurroundings(mouse);

        int moved = 0;
        int nx, ny;

        // **Prüfe, ob das aktuelle Feld eine Ecke oder ein Tunnel ist, aber NICHT (0,0)!**
        if (!(mouse->x == 0 && mouse->y == 0) && countOpenPaths(mouse->x, mouse->y) == 2) {  
            cost[mouse->x][mouse->y] = 2;  // Sofort als vollständig erkundet markieren
        }

        // **1️⃣ Normale Bewegung – Prüfe zuerst neue Richtungen**
        for (int i = 0; i < 3; i++) {
            int checkDir = (mouse->dir + (i == 0 ? 3 : i == 1 ? 0 : 1)) % 4;

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

        if (!moved) {
            performBacktracking(mouse);
        }

    } while (labyrinthErforscht());
    //printCostMatrix(); //zu Testzwecken
}
