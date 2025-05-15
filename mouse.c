#include "mouse.h"
#include "maze.h"
#include <stdio.h>
#include "mockSensors.h"

int mazeUpdated = 0;

// Initialisiert die Maus in der Startposition
void initMouse(Mouse* mouse) {
    mouse->x = 0;  // Start an der Ecke (immer die obere Rechte)
    mouse->y = 0;
    mouse->dir = 1; // Startet nach Osten
}

// Prüft, ob vor der Maus eine Wand ist
int isWall(Mouse* mouse) {
    int x = mouse->x;
    int y = mouse->y;

    switch (mouse->dir) {
        case 0: return hasWall(x, y, 0); // Nach Norden
        case 1: return hasWall(x, y, 1); // Nach Osten
        case 2: return hasWall(x, y, 2); // Nach Süden
        case 3: return hasWall(x, y, 3); // Nach Westen
    }
    return 1; // Sicherheitshalber: Falls etwas schiefgeht, wird eine Wand angenommen
}

// Bewegt die Maus einen Schritt nach vorne, wenn keine Wand da ist
void moveForward(Mouse* mouse) {
    if (!isWall(mouse)) {
        switch (mouse->dir) {
            case 0: if (mouse->y > 0) mouse->y--; break;  // Norden
            case 1: if (mouse->x < MAZE_SIZE - 1) mouse->x++; break;  // Osten
            case 2: if (mouse->y < MAZE_SIZE - 1) mouse->y++; break;  // Süden
            case 3: if (mouse->x > 0) mouse->x--; break;  // Westen
        }
        printf("Maus ist jetzt auf (%d, %d) Richtung: %d\n", mouse->x, mouse->y, mouse->dir); // zun Testen
    }
}

// Dreht die Maus um 90° nach links
void turnLeft(Mouse* mouse) {
    mouse->dir = (mouse->dir + 3) % 4;  // 0 → 3, 1 → 0, 2 → 1, 3 → 2
}

// Dreht die Maus um 90° nach rechts
void turnRight(Mouse* mouse) {
    mouse->dir = (mouse->dir + 1) % 4;  // 0 → 1, 1 → 2, 2 → 3, 3 → 0
}

// Erkennt neue Wände in der Umgebung und aktualisiert das Labyrinth
void scanSurroundings(Mouse* mouse) {
    //scanSurroundingsMock(mouse);

    int x = mouse->x;
    int y = mouse->y;

    if (detectWallSensor(0) && !hasWall(x, y, 0)) { setWall(x, y, 0); mazeUpdated = 1; } // Nord
    if (detectWallSensor(1) && !hasWall(x, y, 1)) { setWall(x, y, 1); mazeUpdated = 1; } // Ost
    if (detectWallSensor(2) && !hasWall(x, y, 2)) { setWall(x, y, 2); mazeUpdated = 1; } // Süd
    if (detectWallSensor(3) && !hasWall(x, y, 3)) { setWall(x, y, 3); mazeUpdated = 1; } // West
}

// Simulierte Sensorfunktion: Hier müsste der echte Sensorwert reinkommen
int detectWallSensor(int direction) {
    // Hier sollte der echte Sensordaten-Abruf stattfinden
    return 0;  // Standardmäßig keine Wand erkannt (zum Testen anpassbar)
}
