#include "queue.h"
#include <stdio.h>

// Initialisiert die Warteschlange
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    
    // Setze alle Werte auf -1 (oder eine andere Initialisierung)
    for (int i = 0; i < QUEUE_SIZE; i++) {
        q->x[i] = -1;
        q->y[i] = -1;
    }
}


// Prüft, ob die Warteschlange leer ist
int isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

// Prüft, ob die Warteschlange voll ist
int isQueueFull(Queue* q) {
    int full = (q->rear + 1) % QUEUE_SIZE == q->front;
    return full;
}

void printQueue(Queue* q) {
    printf("Queue-Inhalt: [");
    int i = q->front;
    while (i != q->rear) {  // Solange es noch Elemente gibt
        printf(" (%d, %d)", q->x[i], q->y[i]);
        i = (i + 1) % QUEUE_SIZE;  // Zyklische Verwaltung beachten
    }
    printf(" ]\n");
}

// Fügt ein Element zur Warteschlange hinzu (mit Wrap-Around)
int enqueue(Queue* q, int x, int y) {
    if (isQueueFull(q)) {
        return -1;
    }
    // Element an aktueller Position speichern
    q->x[q->rear] = x;
    q->y[q->rear] = y;
    q->rear = ((q->rear + 1) % QUEUE_SIZE);  // Wrap-Around beachten
    return 0;  // Erfolg
}


// Entfernt ein Element aus der Warteschlange
int dequeue(Queue* q, int* x, int* y) {
    if (isQueueEmpty(q)) {
        return -1;  // Fehler: Warteschlange leer
    }
    *x = q->x[q->front];
    *y = q->y[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return 0;  // Erfolg
}

