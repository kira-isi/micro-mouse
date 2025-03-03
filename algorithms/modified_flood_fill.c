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
            if (dir == 0 && y > 0 && !hasWall(x, y, 0)) ny--;  // Norden
            if (dir == 1 && x < MAZE_SIZE - 1 && !hasWall(x, y, 1)) nx++;  // Osten
            if (dir == 2 && y < MAZE_SIZE - 1 && !hasWall(x, y, 2)) ny++;  // Süden
            if (dir == 3 && x > 0 && !hasWall(x, y, 3)) nx--;  // Westen

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
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            cost[x][y] = MAX_COST;  // Anfangswert
        }
    }

    initQueue(&floodQueue);  // Initialisiere die Warteschlange

    setGoal();

    // Startwerte zur Queue hinzufügen
    int mid = MAZE_SIZE / 2;
    enqueue(&floodQueue, mid, mid);
    enqueue(&floodQueue, mid - 1, mid);
    enqueue(&floodQueue, mid, mid - 1);
    enqueue(&floodQueue, mid - 1, mid - 1);

    updateModifiedFloodFill();
}

// Führt Modified Flood-Fill aus und steuert die Maus
void runModifiedFloodFill(Mouse* mouse) {
    initModifiedFloodFill();
    do {
        scanSurroundings(mouse);
        if (mazeUpdated) {  // Falls neue Wände erkannt wurden
            initQueue(&floodQueue);
            enqueue(&floodQueue, mouse->x, mouse->y);
            updateModifiedFloodFill();
        }
        moveToLowestCost(mouse);

    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == (MAZE_SIZE / 2) - 1) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == (MAZE_SIZE / 2) - 1));
}