#include "algorithms.h"
#include "../utils/queue.h"
#include "stdio.h"

Queue floodQueue;  // Erstelle eine Warteschlange für den Flood-Fill

// Aktualisiert nur betroffene Felder der Kostenmatrix
void updateModifiedFloodFill() {
    while (!isQueueEmpty(&floodQueue)) {
        int x, y;
        dequeue(&floodQueue, &x, &y);
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = x, ny = y;
            if (dir == 0 && y > 0 && !hasWall(x, y, 0)) ny--;
            else if (dir == 1 && x < MAZE_SIZE - 1 && !hasWall(x, y, 1)) nx++;
            else if (dir == 2 && y < MAZE_SIZE - 1 && !hasWall(x, y, 2)) ny++;
            else if (dir == 3 && x > 0 && !hasWall(x, y, 3)) nx--;
            else continue;

            if (cost[nx][ny] > cost[x][y] + 1) {
                cost[nx][ny] = cost[x][y] + 1;
                enqueue(&floodQueue, nx, ny);
            }
        }
    }
    //printCostMatrix();  // zum Testen
}

// Initialisiert Modified Flood-Fill
void initModifiedFloodFill() {
    setCostMatrixMax();
    initQueue(&floodQueue);  // Initialisiere die Warteschlange

    setGoal();
    setCostMatrixGoals(&floodQueue);

    updateModifiedFloodFill();
}

// Führt Modified Flood-Fill aus und steuert die Maus
void runModifiedFloodFill(Mouse* mouse) {
    initModifiedFloodFill();
    do {
        scanSurroundings(mouse);
        if (mazeUpdated) {  // Falls neue Wände erkannt wurden
            initModifiedFloodFill();
            mazeUpdated=0;
        }
        moveToLowestCost(mouse);

    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == (MAZE_SIZE / 2) - 1) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == (MAZE_SIZE / 2) - 1));
}