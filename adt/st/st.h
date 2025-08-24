#ifndef ST_H
#define ST_H

#include "../item.h"

// Symbol Table (ST) structure definition
typedef struct symtab *ST;

// Initializes a symbol table with a given maximum size and load factor r
ST STinit(int maxN, float r);

// Inserts an item into the symbol table
void STinsert(ST st, Item val);

// Searches for an item by key in the symbol table
Item STsearch(ST st, Key k);

// Deletes an item from the symbol table by key
void STdelete(ST st, Key k);

// Displays all items in the symbol table
void STdisplay(ST st);

// Frees memory allocated for the symbol table
void STfree(ST st);

// Returns the number of elements in the symbol table
int STcount(ST st);

// Checks if the symbol table is empty
int STempty(ST st);

#endif // ST_H
