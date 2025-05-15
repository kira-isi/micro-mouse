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

        // Drehe zur Zielrichtung und gehe einen Schritt zurück
        int backDir = getDirectionToTarget(mouse, prevX, prevY);
        turnToDirection(mouse, backDir);
        moveForward(mouse);  // Jetzt steht Maus auf prevX,prevY

        // Prüfe: gibt es hier noch offene Wege?
        for (int d = 0; d < 4; d++) {
            int tx = mouse->x, ty = mouse->y;
            if (d == 0 && !hasWall(tx, ty, 0)) ty--;
            else if (d == 1 && !hasWall(tx, ty, 1)) tx++;
            else if (d == 2 && !hasWall(tx, ty, 2)) ty++;
            else if (d == 3 && !hasWall(tx, ty, 3)) tx--;
            else continue;

            if (tx >= 0 && tx < MAZE_SIZE && ty >= 0 && ty < MAZE_SIZE &&
                cost[tx][ty] == 0) {
                // wir haben ein unerforschtes Nachbarfeld → stoppe hier
                return;
            }
        }

        // Wenn nichts offen: setze dieses Feld als erledigt und weiter zurück
        cost[mouse->x][mouse->y] = 2;
    }

    printf("Fehler: Stack ist leer, aber Backtracking nötig! Notfall-Stopp.\n");
    exit(1);
}



void runDFS_Target(Mouse* mouse) {
    initStack(&stack);

    int startOpenPaths = countOpenPaths(mouse->x, mouse->y);
    if (startOpenPaths == 1) {
        cost[mouse->x][mouse->y] = 2;  // vollständig erkundet
    } else {
        cost[mouse->x][mouse->y] = 1;  // nur besucht
    }

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
                    push(&stack, mouse->x, mouse->y);
                    moveForward(mouse);
                    cost[mouse->x][mouse->y] = 1;  // Markiere als besucht
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

        //printCostMatrix(); //zum Testen

    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == (MAZE_SIZE / 2) - 1) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == (MAZE_SIZE / 2) - 1));
}