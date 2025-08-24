#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// List based on an array implementation, still unordered.

// Function to initialize an empty list
LIST LISTinit() {
    LIST list = (LIST)malloc(sizeof(struct list));
    if (!list) {
        return NULL; // Memory allocation failed
    }
    list->items = (Item*)malloc(10 * sizeof(Item)); // Initially the capacity is 10
    list->size = 0;
    list->capacity = 10;
    return list;
}

// Function to resize the array when needed (double the capacity)
void resize(LIST list) {
    list->capacity *= 2;
    list->items = (Item*)realloc(list->items, list->capacity * sizeof(Item));
}

// Inserts an item at the head of the list
void LISTinsHead(LIST list, Item val) {
    if (list->size == list->capacity) {
        resize(list);  // Double the capacity if the list is full
    }
    
    // Manually shift the elements to the right
    for (int i = list->size - 1; i >= 0; i--) {
        list->items[i + 1] = list->items[i];
    }
    
    // Insert the new item at the head
    list->items[0] = val;
    list->size++;
}

// Deletes the first item from the list (head)
void LISTdelHead(LIST list) {
    if (list->size == 0) {
        return; // Empty list, nothing to do
    }

    // Manually shift the elements to the left
    for (int i = 0; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }

    list->size--;
}

// Inserts an item at the tail of the list (inefficient version)
void LISTinsTail(LIST list, Item val) {
    if (list->size == list->capacity) {
        resize(list);  // Double the capacity if the list is full
    }
    list->items[list->size] = val;
    list->size++;
}

// Inserts an item at the tail of the list (efficient version with tail pointer)
void LISTinsTailFast(LIST list, Item val) {
    if (list->size == list->capacity) {
        resize(list);  // Double the capacity if the list is full
    }
    list->items[list->size] = val;
    list->size++;
}

// Searches for an item in the list by key
Item LISTsearch(LIST list, Key key) {
    for (int i = 0; i < list->size; i++) {
        if (list->items[i].key == key) {
            return list->items[i];
        }
    }
    return NULL; // Item not found
}

// Deletes a specific item from the list
void LISTdelNode(LIST list, Item val) {
    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (list->items[i].key == val.key) {
            found = 1;
        }
        if (found && i < list->size - 1) {
            list->items[i] = list->items[i + 1]; // Shift elements to the left
        }
    }
    if (found) {
        list->size--;
    }
}

// Returns the element at the specified index (random access)
Item LISTget(LIST list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL; // Index out of bounds
    }
    return list->items[index];
}

// Modifies the element at the specified index
void LISTset(LIST list, int index, Item val) {
    if (index < 0 || index >= list->size) {
        return; // Index out of bounds
    }
    list->items[index] = val;
}

// Returns the size of the list
int LISTsize(LIST list) {
    return list->size;
}

// Checks if an item exists in the list
int LISTcontains(LIST list, Item val) {
    for (int i = 0; i < list->size; i++) {
        if (list->items[i].key == val.key) {
            return 1; // Item found
        }
    }
    return 0; // Item not found
}

// Clears all elements from the list
void LISTclear(LIST list) {
    list->size = 0;
}

// Returns an array with all elements in the list
Item* LISTtoArray(LIST list) {
    Item* arrayCopy = (Item*)malloc(list->size * sizeof(Item));
    memcpy(arrayCopy, list->items, list->size * sizeof(Item));
    return arrayCopy;
}
