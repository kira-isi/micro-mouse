#include "algorithms.h"
#include "..\utils\priority_queue.h"
#include "..\utils\stack.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

PriorityQueue pq;
Stack stackASern;
int goalX = MAZE_SIZE / 2;
int goalY = MAZE_SIZE / 2;

// Heuristik-Funktion: Manhattan-Distanz
int heuristic(int x, int y) {
    return abs(x - goalX) + abs(y - goalY);
}

// Initialisierung von A*
void initAStar(int startX, int startY) {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            cost[x][y] = MAX_COST;
            previous[x][y] = (Coordinates){-1, -1};
        }
    }
    cost[startX][startY] = 0;
    initPriorityQueue(&pq);
    pqueue_enqueue(&pq, startX, startY, heuristic(startX, startY));
}

// A*-Algorithmus: Berechnet die besten Wege
void updateAStar() {
    int dx[] = {0, 1, 0, -1};  // Bewegungsrichtungen: N, O, S, W
    int dy[] = {-1, 0, 1, 0};

    while (!isPriorityQueueEmpty(&pq)) {
        int x, y;
        pqueue_dequeue(&pq, &x, &y);

        if (x == goalX && y == goalY) break;  // Ziel erreicht -> früh abbrechen

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < MAZE_SIZE && ny >= 0 && ny < MAZE_SIZE && !hasWall(x, y, i)) {
                int newCost = cost[x][y] + 1;
                if (newCost < cost[nx][ny]) {  
                    cost[nx][ny] = newCost;
                    previous[nx][ny] = (Coordinates){x, y};  // Speichert die nächste Bewegung
                    pqueue_enqueue(&pq, nx, ny, newCost + heuristic(nx, ny));
                }                
            }
        }
    }
}

// Lässt die Maus dem besten Pfad folgen
void runAstar(Mouse* mouse) {
    initAStar(mouse->x, mouse->y);
    updateAStar();
    reconstructPath(&stackASern, goalX, goalY);
    do {
        scanSurroundings(mouse);

        if (mazeUpdated) {
            initAStar(mouse->x, mouse->y);
            updateAStar();
            reconstructPath(&stackASern, goalX, goalY);
            mazeUpdated = 0;
        }

        // **Falls der Stack leer ist, ist das Ziel erreicht**
        if (isStackEmpty(&stackASern)) {
            printf("Fehler: Stack leer!\n");
            break;
        }

        // **Nächstes Feld aus dem Stack holen**
        int nextX, nextY;
        pop(&stackASern, &nextX, &nextY);

        int bestDir = getDirectionToTarget(mouse, nextX, nextY);
        turnToDirection(mouse, bestDir);
        moveForward(mouse);
    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2 - 1) &&
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2 - 1));
}