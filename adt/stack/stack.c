#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

// top is the always the index of the last element of the array so the top of the stack
// it starts with -1
// push -> stack[++top]
// pop -> stack[top--]

// Stack structure definition
struct stack {
    Item *array;    
    int top;        
    int capacity;   
};

// Initializes an empty stack with the given maximum size
STACK STACKinit(int max_size) {
    STACK stack = malloc(sizeof(struct stack));
    if (stack == NULL) {
        return NULL;  // Failed to allocate memory
    }
    stack->array = malloc(max_size * sizeof(Item));
    if (stack->array == NULL) {
        free(stack);
        return NULL;  // Failed to allocate memory for the array
    }
    stack->top = -1; // Stack is empty
    stack->capacity = max_size;
    return stack;
}

// Pushes an item onto the stack
void STACKpush(STACK stack, Item val) {
    if (stack->top == stack->capacity - 1) {
        printf("Error: Stack overflow\n");
        return;  // Stack is full, cannot push
    }
    stack->array[++stack->top] = val;  // Increment top and add item
}

// Pops an item from the stack
Item STACKpop(STACK stack) {
    if (stack->top == -1) {
        printf("Error: Stack underflow\n");
        return ITEMsetvoid();  // Return a void item in case of underflow
    }
    return stack->array[stack->top--];  // Return top item and decrement top
}

// Peeks the top item of the stack without popping it
Item STACKpeek(STACK stack) {
    if (stack->top == -1) {
        printf("Error: Stack is empty\n");
        return ITEMsetvoid();  // Return a void item if the stack is empty
    }
    return stack->array[stack->top];  // Return top item
}

// Returns the size of the stack
int STACKsize(STACK stack) {
    return stack->top + 1;  // Size is top index + 1
}

// Checks if the stack is empty
int STACKisEmpty(STACK stack) {
    return stack->top == -1;  // Stack is empty if top is -1
}

// Checks if the stack is full
int STACKisFull(STACK stack) {
    return stack->top == stack->capacity - 1;  // Stack is full if top is at the last index
}

// Clears the stack by resetting the top index
void STACKclear(STACK stack) {
    stack->top = -1;  // Simply reset the stack to an empty state
}

// Frees the stack's memory
void STACKfree(STACK stack) {
    free(stack->array);  // Free the array holding the items
    free(stack);         // Free the stack structure itself
}
