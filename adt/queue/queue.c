#include "queue.h"
#include <stdlib.h>

typedef struct node* link;

struct node {
    Item val;
    link next;
};

struct queue {
    link front;  
    link rear;   
    int size;   
};

// Initializes an empty queue
QUEUE QUEUEinit() {
    QUEUE q = malloc(sizeof(*q));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// Inserts an item at the end of the queue
void QUEUEenqueue(QUEUE queue, Item val) {
    link newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) return;
    
    newNode->val = val;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// Removes an item from the front of the queue
Item QUEUEdequeue(QUEUE queue) {
    if (queue->front == NULL) return ITEMsetvoid();  // Queue is empty
    
    link temp = queue->front;
    Item val = temp->val;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;  // Queue is now empty
    
    free(temp);
    queue->size--;
    return val;
}

// Returns the item at the front of the queue without removing it
Item QUEUEpeek(QUEUE queue) {
    if (queue->front == NULL) return ITEMsetvoid();  // Queue is empty
    return queue->front->val;
}

// Checks if the queue is empty
int QUEUEisEmpty(QUEUE queue) {
    return queue->front == NULL;
}

// Returns the number of items in the queue
int QUEUEsize(QUEUE queue) {
    return queue->size;
}

// Clears all elements in the queue
void QUEUEclear(QUEUE queue) {
    while (queue->front != NULL) {
        QUEUEdequeue(queue);
    }
}

// Returns an array with all elements in the queue
Item* QUEUEtoArray(QUEUE queue) {
    Item* arr = malloc(queue->size * sizeof(Item));
    if (arr == NULL) return NULL;
    
    link temp = queue->front;
    for (int i = 0; temp != NULL; i++, temp = temp->next) {
        arr[i] = temp->val;
    }
    return arr;
}
