#include "stack.h"
#include <stdio.h>

// Stack initialisieren
void initStack(Stack* s) {
    s->stackTop = -1;
}

// Element auf den Stack legen
void push(Stack* s, int x, int y) {
    if (s->stackTop < STACK_SIZE - 1) {
        s->stackTop++;
        s->lastX[s->stackTop] = x;
        s->lastY[s->stackTop] = y;
    } else {
        printf("Fehler: Stack ist voll!\n");
    }
}

// Element vom Stack nehmen
void pop(Stack* s, int* x, int* y) {
    if (s->stackTop >= 0) {
        *x = s->lastX[s->stackTop];
        *y = s->lastY[s->stackTop];
        s->stackTop--;
    } else {
        printf("Fehler: Stack ist leer!\n");
    }
}

// Prüfen, ob der Stack leer ist
int isStackEmpty(Stack* s) {
    return s->stackTop < 0;
}

// Stack-Inhalt ausgeben
void printStack(Stack* s) {
    if (s->stackTop < 0) {
        printf("Stack ist leer.\n");
        return;
    }

    printf("Aktueller Stack-Inhalt (von oben nach unten):\n");
    for (int i = s->stackTop; i >= 0; i--) {
        printf("(%d, %d)\n", s->lastX[i], s->lastY[i]);
    }
    printf("\n");
}