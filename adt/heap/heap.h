#ifndef HEAP_H
#define HEAP_H

#include "../item.h"

typedef struct heap* Heap;

Heap HEAPinit(int maxN);
void HEAPfree(Heap h);
void HEAPfill(Heap h, Item item);
void HEAPdisplay(Heap h);
void HEAPify(Heap h, int i);
void HEAPbuild(Heap h);
void HEAPsort(Heap h);

#endif