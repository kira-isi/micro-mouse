#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MAX_QUEUE_SIZE 256

typedef struct {
    int x, y;
    int priority;  // f(x) = g(x) + h(x)
} PQNode;

typedef struct {
    PQNode nodes[MAX_QUEUE_SIZE];
    int size;
} PriorityQueue;

void initPriorityQueue(PriorityQueue* pq);
void pqueue_enqueue(PriorityQueue* pq, int x, int y, int priority);
int pqueue_dequeue(PriorityQueue* pq, int* x, int* y);
int isPriorityQueueEmpty(PriorityQueue* pq);
void printPriorityQueue(PriorityQueue* pq);

#endif