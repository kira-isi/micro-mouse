#include "algorithms.h"
#include <stdio.h>

#include "../test.h"

/// Datei für gemeinsam genutze Funktionen ///

//Kostenmatrix wird hier gespeichert
int cost[MAZE_SIZE][MAZE_SIZE];
Coordinates previous[MAZE_SIZE][MAZE_SIZE];

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

        // Richtung prüfen und gültige Nachbarzelle berechnen
        if (dir == 0 && y > 0 && !hasWall(x, y, 0)) ny--;
        else if (dir == 1 && x < MAZE_SIZE - 1 && !hasWall(x, y, 1)) nx++;
        else if (dir == 2 && y < MAZE_SIZE - 1 && !hasWall(x, y, 2)) ny++;
        else if (dir == 3 && x > 0 && !hasWall(x, y, 3)) nx--;
        else continue; // keine gültige Bewegung → nächste Richtung

        if (cost[nx][ny] < cost[x][y] && cost[nx][ny] < minCost) {
            minCost = cost[nx][ny];
            minDir = dir;
        }
        
    }
    if (minDir != -1) {
        turnToDirection(mouse, minDir);
        moveForward(mouse);
    } else { printCostMatrix(); printf("Keine gueltige Richtung mit niedrigeren Kosten von (%d, %d)\n", x, y); }
}


void turnToDirection(Mouse* mouse, int targetDir) {
    if (mouse->dir == targetDir) {
        return;  // **Keine Drehung nötig, Maus schaut schon richtig**
    }

    int rightTurns = (targetDir - mouse->dir + 4) % 4;  // Anzahl der Schritte mit `turnRight()`
    int leftTurns = (mouse->dir - targetDir + 4) % 4;   // Anzahl der Schritte mit `turnLeft()`

    if (rightTurns <= leftTurns) {  
        for (int i = 0; i < rightTurns; i++) {
            turnRight(mouse);
        }
    } else {
        for (int i = 0; i < leftTurns; i++) {
            turnLeft(mouse);
        }
    }
}

int countOpenPaths(int x, int y) {
    int openPaths = 0;
    for (int i = 0; i < 4; i++) {
        if (!hasWall(x, y, i)) {  // Prüfe, ob es physisch eine offene Richtung gibt
            openPaths++;
        }
    }
    //printf("Offen in %d Richtungen\n", openPaths); //zu Testzwecken
    return openPaths;
}

// Hilfsfunktion: Bestimmt die nächste Position basierend auf der Richtung
void getNextPosition(int *x, int *y, int dir) {
    switch (dir) {
        case 0: (*y)--; break;  // Norden
        case 1: (*x)++; break;  // Osten
        case 2: (*y)++; break;  // Süden
        case 3: (*x)--; break;  // Westen
    }
}

// Hilfsfunktion: Bestimmt die Richtung zur Zielposition
int getDirectionToTarget(Mouse* mouse, int targetX, int targetY) {
    if (mouse->x < targetX) return 1;  // Osten
    if (mouse->x > targetX) return 3;  // Westen
    if (mouse->y < targetY) return 2;  // Süden
    if (mouse->y > targetY) return 0;  // Norden
    return mouse->dir;
}

void reconstructPath(Stack* stack, int goalX, int goalY) {
    int x = goalX, y = goalY;
    initStack(stack);  // Stack zurücksetzen

    while (previous[x][y].x != -1 && previous[x][y].y != -1) {
        push(stack, x, y);  // Speichere das aktuelle Feld im Stack

        int prevX = previous[x][y].x;
        int prevY = previous[x][y].y;

        x = prevX;
        y = prevY;
    }
}

void setCostMatrixMax(){
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            cost[x][y] = MAX_COST;  // Anfangswert
        }
    }
}

void setCostMatrixGoals(Queue* queue){
    int mid = MAZE_SIZE / 2;
    enqueue(queue, mid, mid);
    enqueue(queue, mid - 1, mid);
    enqueue(queue, mid, mid - 1);
    enqueue(queue, mid - 1, mid - 1);
}