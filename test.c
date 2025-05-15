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

void createTestMaze() {
    initMaze();

    // Sekror links oben
    setWall(0, 0, 2); 
    setWall(1, 0, 1);
    setWall(2, 0, 2);

    setWall(0, 1, 1); 
    setWall(1, 1, 2);
    setWall(2, 1, 1);
    setWall(3, 1, 2);
    setWall(3, 1, 1);

    setWall(0, 2, 1); 
    setWall(2, 2, 2);

    setWall(0, 3, 1); 
    setWall(1, 3, 2);

    // Sekror rechts oben
    setWall(4, 0, 2);
    setWall(6, 0, 2);
    setWall(7, 0, 2);

    setWall(5, 1, 1); 
    setWall(6, 1, 2);

    setWall(4, 2, 1);
    setWall(5, 2, 2);
    setWall(6, 2, 1);

    setWall(5, 3, 1); 
    setWall(7, 3, 2);

    // Sekror links unten
    setWall(0, 5, 1); 
    setWall(1, 5, 1);
    setWall(2, 5, 1); 
    setWall(3, 5, 2);

    setWall(0, 6, 1); 
    setWall(1, 6, 1);
    setWall(3, 6, 2);

    setWall(0, 7, 1); 
    setWall(2, 7, 1);

    // Sekror rechts unten
    setWall(6, 4, 1); 
    setWall(5, 4, 2);

    setWall(4, 5, 1); 

    setWall(4, 6, 2);
    setWall(5, 6, 2);
    setWall(5, 6, 1); 
    setWall(6, 6, 1);

    setWall(6, 7, 1);

    //Box um das Ziel
    setWall(4, 3, 0); // Nordwand von (4,3)
    setWall(4, 3, 1); // Ostwand von (4,3)
    setWall(3, 3, 0); // Nordwand von (3,3)
    setWall(3, 3, 3); // Westwand von (3,3)


    setWall(4, 4, 1); // Ostwand von (4,4)
    setWall(4, 4, 2); // Südwand von (4,4)
    setWall(3, 4, 3); // Westwand von (3,4)
    // Eingang Ziel setWall(3, 4, 2); // Südwand von (3,4)

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
