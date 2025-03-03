#include "algorithms.h"
#include <stdio.h>
/// Datei für gemeinsam genutze Funktionen ///

//Kostenmatrix wird hier gespeichert
int cost[MAZE_SIZE][MAZE_SIZE];

//Ziel des Labyrinths setzen
void setGoal() {
    int mid = MAZE_SIZE / 2;
    cost[mid][mid] = 0;
    cost[mid - 1][mid] = 0;
    cost[mid][mid - 1] = 0;
    cost[mid - 1][mid - 1] = 0;
}


//Funktion zum Testen Ausgabe der Kostenmatrix
void printCostMatrix() {
    for (int y = 0; y < MAZE_SIZE; y++) {
        for (int x = 0; x < MAZE_SIZE; x++) {
            if (cost[x][y] == MAX_COST) {
                printf(" ## ");  // Wände oder unerreichbare Bereiche
            } else {
                printf(" %2d ", cost[x][y]);  // Kostenwerte
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Bewegt die Maus in Richtung der kleinsten Kosten
void moveToLowestCost(Mouse* mouse) {
    int x = mouse->x;
    int y = mouse->y;
    int minDir = -1;
    int minCost = MAX_COST;

    for (int dir = 0; dir < 4; dir++) {
        int nx = x, ny = y;
        if (dir == 0 && y > 0 && !hasWall(x, y, 0)) ny--;  // Norden
        if (dir == 1 && x < MAZE_SIZE - 1 && !hasWall(x, y, 1)) nx++;  // Osten
        if (dir == 2 && y < MAZE_SIZE - 1 && !hasWall(x, y, 2)) ny++;  // Süden
        if (dir == 3 && x > 0 && !hasWall(x, y, 3)) nx--;  // Westen

        if (cost[nx][ny] < minCost) {
            minCost = cost[nx][ny];
            minDir = dir;
        }
    }

    // Drehen, wenn nötig
    if (minDir != -1 && minDir != mouse->dir) {
        if ((mouse->dir + 1) % 4 == minDir) {
            turnRight(mouse);
        } else if ((mouse->dir + 3) % 4 == minDir) {
            turnLeft(mouse);
        } else {
            turnRight(mouse);
            turnRight(mouse);
        }
    }

    // Vorwärts bewegen
    moveForward(mouse);
}