#include "algorithms.h"

void updateBellmanFord() {
    int changed;
    do {
        changed = 0;
        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++) {
                if (cost[x][y] < MAX_COST) {  // Nur Felder mit gültigem Wert bearbeiten
                    for (int dir = 0; dir < 4; dir++) {
                        int nx = x, ny = y;

                        if (dir == 0 && y > 0 && !hasWall(x, y, 0)) ny--;
                        else if (dir == 1 && x < MAZE_SIZE - 1 && !hasWall(x, y, 1)) nx++;
                        else if (dir == 2 && y < MAZE_SIZE - 1 && !hasWall(x, y, 2)) ny++;
                        else if (dir == 3 && x > 0 && !hasWall(x, y, 3)) nx--;
                        else continue; // ungültige Bewegung → überspringen

                        if (cost[nx][ny] > cost[x][y] + 1) {  // Aktualisierung prüfen
                            cost[nx][ny] = cost[x][y] + 1;
                            changed = 1;
                        }
                    }
                }
            }
        }
    } while (changed);  // Wiederholen, bis keine Änderungen mehr auftreten
    //printCostMatrix(); // zum Testen
}


void initBellmanFord() {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            cost[x][y] = MAX_COST;  // Hoher Wert für unerreichbare Felder
        }
    }
    setGoal();
    updateBellmanFord(); // Erstes Mal durchrechnen mit den zu Beginn vorhandenen Infos
}

void runBellmanFord(Mouse* mouse) {
    initBellmanFord();  // Setzt die Kostenmatrix und berechnet die erste Lösung
    do {
        scanSurroundings(mouse); // Umgebung scannen
        if (mazeUpdated) {  // Falls neue Wände erkannt wurden
            initBellmanFord();
            mazeUpdated = 0;
        }

        moveToLowestCost(mouse);  // Kürzesten Weg weiterverfolgen

    } while (!(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2) &&
             !(mouse->x == MAZE_SIZE / 2 && mouse->y == MAZE_SIZE / 2 - 1) &&
             !(mouse->x == MAZE_SIZE / 2 - 1 && mouse->y == MAZE_SIZE / 2 - 1));
}