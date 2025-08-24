#ifndef PQUEUE_H
#define PQUEUE_H

#include "../item.h"

typedef struct pqueue *PQ;

PQ PQinit(int maxN);
void PQtree(PQ pq);
int PQempty (PQ pq);
void PQinsert (PQ pq, Item val);
Item PQextractMax (PQ pq);
Item PQshowMax (PQ pq);
void PQdisplay(PQ pq);
int PQsiZe(PQ pq);
void PQchange (PQ pq, Item val);

#endif
