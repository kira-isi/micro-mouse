#ifndef QUEUE_H
#define QUEUE_H

#include "../maze.h"

#define QUEUE_SIZE (MAZE_SIZE * MAZE_SIZE)  // Maximale Anzahl an Elementen

typedef struct {
    int x[QUEUE_SIZE];
    int y[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q);
int isQueueEmpty(Queue* q);
int enqueue(Queue* q, int x, int y);
int dequeue(Queue* q, int* x, int* y);
void printQueue(Queue* q);

#endif