#include "test.h"
#include <stdio.h>

// Erstellt ein leeres Labyrinth (nur Außenwände)
void createEmptyMaze() {
    initMaze();
    printMaze();
}

// Erstellt ein Labyrinth mit einem Block in der Mitte
void createBlockedCenterMaze() {
    initMaze();

    // Setzt explizit Wände um den Block herum
    setWall(4, 3, 0); // Nordwand von (4,3)
    setWall(4, 3, 1); // Ostwand von (4,3)
    setWall(3, 3, 0); // Nordwand von (3,3)
    setWall(3, 3, 3); // Westwand von (3,3)

    setWall(4, 4, 1); // Ostwand von (4,4)
    setWall(4, 4, 2); // Südwand von (4,4)
    // Eingang zum Ziel // setWall(3, 4, 3); // Westwand von (3,4)
    setWall(3, 4, 2); // Südwand von (3,4)

    printMaze();
}

// Erstellt ein Labyrinth mit einem schmalen Pfad in der Mitte
void createNarrowPathMaze() {
    initMaze();

    // Linke Wände setzen (trennt Zeile 0 und 1)
    setWall(1, 0, 2); 
    setWall(2, 0, 2);
    setWall(3, 0, 2);

    // Sackgasse
    //setWall(3, 0, 1);

    // Rechte Wände setzen (trennt Spalten 3 und 4)
    setWall(4, 1, 3);
    setWall(4, 2, 3);

    //Box um das Ziel
    // Eingang Ziel setWall(4, 3, 0); // Nordwand von (4,3)
    setWall(4, 3, 1); // Ostwand von (4,3)
    setWall(3, 3, 0); // Nordwand von (3,3)
    setWall(3, 3, 3); // Westwand von (3,3)

    setWall(4, 4, 1); // Ostwand von (4,4)
    setWall(4, 4, 2); // Südwand von (4,4)
    setWall(3, 4, 3); // Westwand von (3,4)
    setWall(3, 4, 2); // Südwand von (3,4)

    printMaze();
}

// Gibt das Labyrinth grafisch aus
void printMaze() {
    for (int y = 0; y < MAZE_SIZE; y++) {
        // Erste Zeile mit oberen Wänden
        for (int x = 0; x < MAZE_SIZE; x++) {
            printf("+");
            if (hasWall(x, y, 0)) printf("---");  // Obere Wand
            else printf("   ");  // Kein obere Wand
        }
        printf("+\n");

        // Zweite Zeile mit linken Wänden und Feldern
        for (int x = 0; x < MAZE_SIZE; x++) {
            if (hasWall(x, y, 3)) printf("|  ");  // Linke Wand
            else printf("   ");  // Keine linke Wand

            printf(" ");  // Platz für Maus oder freie Fläche
        }
        printf("|\n");
    }

    // Korrekte untere Begrenzung basierend auf den tatsächlichen Wänden
    for (int x = 0; x < MAZE_SIZE; x++) {
        printf("+");
        if (hasWall(x, MAZE_SIZE - 1, 2)) printf("---");  // Falls untere Wand existiert
        else printf("   ");  // Falls keine untere Wand existiert
    }
    printf("+\n");
}
