#ifndef QUEUE_H
#define QUEUE_H

#include "../item.h"

// FIFO extraction policy
// think of the queue at the supermarket
// it is generally implemented with a linked list as we have to insert at the end
// and extract from the start

// Definition of the queue structure (internal representation)
typedef struct queue* QUEUE;

// Initializes an empty queue
QUEUE QUEUEinit();

// Inserts an item at the end of the queue (enqueuing)
void QUEUEenqueue(QUEUE queue, Item val);

// Removes an item from the front of the queue (dequeuing)
Item QUEUEdequeue(QUEUE queue);

// Returns the item at the front of the queue without removing it
Item QUEUEpeek(QUEUE queue);

// Checks if the queue is empty
int QUEUEisEmpty(QUEUE queue);

// Returns the number of items in the queue
int QUEUEsize(QUEUE queue);

// Clears all elements in the queue
void QUEUEclear(QUEUE queue);

// Returns an array with all elements in the queue
Item* QUEUEtoArray(QUEUE queue);

#endif // QUEUE_H
