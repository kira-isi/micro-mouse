#include <stdio.h>
#include <windows.h>
#include "algorithms/algorithms.h"
#include "test.h"
#include "mockSensors.h"


int main() {
    Mouse mouse;
    initMouse(&mouse);
    createTestMaze();

    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    double elapsedMicroseconds;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start); // Startzeit messen

    runModifiedFloodFill(&mouse);

    QueryPerformanceCounter(&end); // Endzeit messen
    elapsedMicroseconds = (double)(end.QuadPart - start.QuadPart) * 1e6 / frequency.QuadPart; // Zeit berechnen
    double elapsedMilliseconds = elapsedMicroseconds / 1000.0;
    printf("Ausfuehrungszeit: %.3f ms\n", elapsedMilliseconds);

    return 0;
}