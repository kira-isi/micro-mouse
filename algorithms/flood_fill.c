#include "algorithms.h"
#include <stdio.h>

// Berechnet die Flood-Fill-Kosten für das Labyrinth
void updateFloodFill() {
    int changed;
    do {
        changed = 0;
        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++) {
                if (cost[x][y] < MAX_COST) {
                    for (int dir = 0; dir < 4; dir++) {
                        int nx = x;
                        int ny = y;

                        // gültige Bewegung prüfen
                        if (dir == 0 && y > 0 && !hasWall(x, y, 0)) ny--;
                        else if (dir == 1 && x < MAZE_SIZE - 1 && !hasWall(x, y, 1)) nx++;
                        else if (dir == 2 && y < MAZE_SIZE - 1 && !hasWall(x, y, 2)) ny++;
                        else if (dir == 3 && x > 0 && !hasWall(x, y, 3)) nx--;
                        else continue;  // ungültige Bewegung → überspringen

                        if (cost[nx][ny] > cost[x][y] + 1) {
                            cost[nx][ny] = cost[x][y] + 1;
                            changed = 1;
                        }
                    }
                }
            }
        }
    } while (changed);
}


// Initialisiert die Flood-Fill-Kostenmatrix
void initFloodFill() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            cost[x][y] = MAX_COST;  // Hoher Wert für unerreichbare Felder
        }
    }
    setGoal();

    updateFloodFill(); //erstes Mal durchrechnen mit den zu Beginn vorhandenen Infos
}

// Führt den Flood-Fill-Algorithmus aus und steuert die Maus
void runFloodFill(Mouse* mouse) {
    initFloodFill();
    do {
        scanSurroundings(mouse);  // Wände erkennen   
        if (mazeUpdated) {  // Nur aktualisieren, wenn sich das Labyrinth verändert hat
            initFloodFill();// Matrix aktualisieren
            mazeUpdated=0;
        }
        moveToLowestCost(mouse);  // Maus bewegen
    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == (MAZE_SIZE / 2) - 1) &&
             !(mouse->x == (MAZE_SIZE / 2) - 1 && mouse->y == (MAZE_SIZE / 2) - 1));
}