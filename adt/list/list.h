#ifndef LIST_H
#define LIST_H

#include "../item.h"

// Definition of the list structure (internal representation of the array list)
typedef struct list* LIST;

// Initializes an empty list
// The list is backed by a dynamic array that grows as needed.
LIST LISTinit();

// Inserts an item at the head of the list
// This operation shifts existing elements to the right to make space for the new element.
void LISTinsHead(LIST list, Item val);

// Inserts an item at the tail of the list (inefficient version)
// This operation appends the item at the end of the array, which may require resizing.
void LISTinsTail(LIST list, Item val);

// Inserts an item at the tail of the list (efficient version with a tail pointer)
// This operation appends the item at the end of the array efficiently, resizing if necessary.
void LISTinsTailFast(LIST list, Item val);

// Searches for an item with the specified key in the list
// This performs a linear search through the array to find the item with the matching key.
Item LISTsearch(LIST list, Key key);

// Deletes the first item (head) from the list
// This operation shifts all remaining elements to the left to fill the gap.
void LISTdelHead(LIST list);

// Deletes a specific item from the list
// This operation searches for the item and removes it, shifting subsequent items to the left.
void LISTdelNode(LIST list, Item val);

// Retrieves the element at the specified index (random access)
// Provides constant-time access to any element in the array.
Item LISTget(LIST list, int index);

// Modifies the element at the specified index
// Replaces the item at the given index with the new value.
void LISTset(LIST list, int index, Item val);

// Returns the number of elements in the list
// This operation runs in constant time since the size is maintained.
int LISTsize(LIST list);

// Checks if an item exists in the list
// This performs a linear search through the array to determine if the item is present.
int LISTcontains(LIST list, Item val);

// Clears all elements in the list
// Resets the list size to zero, effectively removing all items.
void LISTclear(LIST list);

// Returns an array with all elements in the list
// Copies all elements from the list into a new array.
Item* LISTtoArray(LIST list);

#endif // LIST_H
