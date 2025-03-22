#ifndef STACK_H
#define STACK_H

#include"..\maze.h"

#define STACK_SIZE (MAZE_SIZE * MAZE_SIZE)  // Max. Anzahl an Feldern im Stack

typedef struct {
    int lastX[STACK_SIZE];
    int lastY[STACK_SIZE];
    int stackTop;
} Stack;

void initStack(Stack* s);
void push(Stack* s, int x, int y);
void pop(Stack* s, int* x, int* y);
int isStackEmpty(Stack* s);
void printStack(Stack* s);

#endif