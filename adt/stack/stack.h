#ifndef STACK_H
#define STACK_H

#include "../item.h"

// LIFO extraction policy
// we can easily avoid the overhead of pointers if we know how many elements
// can be on the stack at the same time (or worse just realloc and waste some time)
// and use an array

// stack is very useful to simulate recursion to avoid stack overflow errors if there 
// are too many recursive calls

typedef struct stack* STACK;

// Initializes an empty stack
STACK STACKinit(int max_size);

// Pushes an item onto the stack
void STACKpush(STACK stack, Item val);

// Pops an item from the stack
Item STACKpop(STACK stack);

// Peeks the top item of the stack without popping
Item STACKpeek(STACK stack);

// Returns the size of the stack
int STACKsize(STACK stack);

// Checks if the stack is empty
int STACKisEmpty(STACK stack);

// Checks if the stack is full
int STACKisFull(STACK stack);

// Clears the stack
void STACKclear(STACK stack);

// Frees the stack's memory
void STACKfree(STACK stack);

#endif // STACK_H
