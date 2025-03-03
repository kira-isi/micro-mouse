#include <stdio.h>
#include "algorithms/algorithms.h"
#include "test.h"

int main() {
    Mouse mouse;
    initMouse(&mouse);
    createNarrowPathMaze();
    runBellmanFord(&mouse);

    return 0;
}