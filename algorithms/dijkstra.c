#include "algorithms.h"
#include "..\utils\queue.h"
#include "..\utils\stack.h"
#include <stdio.h>
#include <limits.h>

Stack stackDijkstra;
Queue queue;


// Initialisierung von Dijkstra
void initDijkstra(int startX, int startY) {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            cost[x][y] = MAX_COST;  // Setze alle Kosten auf unendlich
            previous[x][y] = (Coordinates){-1, -1};
        }
    }
    cost[startX][startY] = 0;  // Startpunkt hat Kosten 0
    initQueue(&queue);
    enqueue(&queue, startX, startY);
}


// Dijkstra-Algorithmus: Berechnet die kürzesten Wege
void updateDijkstra() {
    int dx[] = {0, 1, 0, -1};  // Bewegungsrichtungen: N, O, S, W
    int dy[] = {-1, 0, 1, 0};

    while (!isQueueEmpty(&queue)) {
        int x, y;
        dequeue(&queue, &x, &y);

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < MAZE_SIZE && ny >= 0 && ny < MAZE_SIZE && !hasWall(x, y, i)) {
                int newCost = cost[x][y] + 1;  // Jeder Schritt kostet 1
                
                if (newCost < cost[nx][ny]) {  
                    cost[nx][ny] = newCost;
                    previous[nx][ny] = (Coordinates){x, y};  // Speichere die Richtung, aus der das Feld erreicht wurde
                    enqueue(&queue, nx, ny);
                }                
            }
        }
    }
}



// Lässt die Maus dem kürzesten Pfad folgen
void runDijkstra(Mouse* mouse) {
    initDijkstra(mouse->x, mouse->y);
    updateDijkstra();  // Erstes vollständiges Dijkstra-Update

    int goalX = MAZE_SIZE / 2;
    int goalY = MAZE_SIZE / 2;

    reconstructPath(&stackDijkstra, goalX, goalY);  // Speichert den Pfad in den Stack

    do {
        scanSurroundings(mouse);

        // Falls sich das Labyrinth verändert hat, müssen wir Dijkstra erneut berechnen
        if (mazeUpdated) {
            //printf("Maze wurde aktualisiert – Berechne Dijkstra erneut...\n");
            initDijkstra(mouse->x, mouse->y);
            updateDijkstra();
            reconstructPath(&stackDijkstra, goalX, goalY);
            mazeUpdated = 0;  // Zurücksetzen
        }

        // **Falls der Stack leer ist, ist das Ziel erreicht**
        if (isStackEmpty(&stackDijkstra)) {
            printf("Fehler: Stack leer!\n");
            break;
        }

        // **Nächstes Feld aus dem Stack holen**
        int nextX, nextY;
        pop(&stackDijkstra, &nextX, &nextY);

        int bestDir = getDirectionToTarget(mouse, nextX, nextY);
        turnToDirection(mouse, bestDir);
        moveForward(mouse);
    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2 - 1) &&
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2 - 1));
}