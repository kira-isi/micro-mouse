#include "priority_queue.h"

void initPriorityQueue(PriorityQueue* pq) {
    pq->size = 0;
}

void pqueue_enqueue(PriorityQueue* pq, int x, int y, int priority) {
    if (pq->size >= MAX_QUEUE_SIZE) return;

    int i = pq->size;
    while (i > 0 && pq->nodes[i - 1].priority > priority) {  
        pq->nodes[i] = pq->nodes[i - 1];  
        i--;
    }
    pq->nodes[i] = (PQNode){x, y, priority};
    pq->size++;
}

int pqueue_dequeue(PriorityQueue* pq, int* x, int* y) {
    if (pq->size == 0) return 0;
    *x = pq->nodes[0].x;
    *y = pq->nodes[0].y;
    pq->size--;
    for (int i = 0; i < pq->size; i++) {
        pq->nodes[i] = pq->nodes[i + 1];
    }
    return 1;
}

int isPriorityQueueEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

#include <stdio.h>

void printPriorityQueue(PriorityQueue* pq) {
    printf("Priority Queue Inhalt (Größe: %d):\n", pq->size);
    for (int i = 0; i < pq->size; i++) {
        printf("  [%d] x: %d, y: %d, f(x): %d\n", i, pq->nodes[i].x, pq->nodes[i].y, pq->nodes[i].priority);
    }
    if (pq->size == 0) {
        printf("  (leer)\n");
    }
    printf("\n");
}
