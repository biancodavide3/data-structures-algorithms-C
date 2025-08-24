// implementazione basata su heap
// e' migliore rispetto a quelle con vettore lista (ordinati e non)
// poiche' abbiamo un costo logaritmo per inserzione e estrazione dell'elemento
// a priorita' massima o minima (dipende dalla convenzione)

#include "PQ.h"
#include "../heap/heap.h"
#include "../item.h"
#include <stdlib.h>
#include <stdio.h>

int LEFT(int i) {
    return 2 * i + 1;
}

int RIGHT (int i) {
    return 2 * i + 2;
}

int PARENT(int i) {
    return (i - 1) / 2;
}

struct pqueue {
    Item *A;
    int heapsize;
};

PQ PQinit(int maxN) {
    PQ pq;
    pq = (struct pqueue*) malloc(sizeof (struct pqueue));
    pq->A = (Item *)malloc(maxN * sizeof(Item));
    return pq;
}

void PQfree(PQ pq) {
    free(pq->A);
    free(pq);
}

int PQempty (PQ pq) {
    return pq->heapsize == 0;
}

int PQsize(PQ pq) {
    return pq->heapsize;
}

// usando la heap sappiamo che l'elemento a massima priorita' sara' il primo del vettore
// e show indica che lo prendiamo senza pero' rimuoverlo
Item PQshowMax (PQ pq) {
    return pq->A[0];
}

void PQdisplay(PQ pq) {
    int i;
    for (i = 0; i < pq->heapsize; i++)
        ITEMshow(pq->A[i]);
}

// per inserire un elemento mantenendo la proprieta' funzionale
// della heap immagino innanzi tutto di inserire una nuova foglia nell'ultimo livello
// piu' a destra possibile (virtualmente) e inizio a confrontare con il padre
// se il padre e' minore della chiave del val che sto inserendo allora
// lo faccio scendere in questa foglia e poi continuo a confrontare con il successivo
// parent e farlo scendere fino a quando non trovo un parent che e' maggiore
// della key del val che voglio inserire, appena lo trovo piazzo il val come figlio di
// questo parent, opero dal basso verso l'alto
// T(n) = O(logn)
void PQinsert(PQ pq, Item val) {
    int i = pq->heapsize -1;
    pq->heapsize++;
    while (i >= 1 && KEYcompare(KEYget(val), KEYget(pq->A[PARENT(i)])) == 1) {
        pq->A[i] = pq->A[PARENT(i)];
        i = PARENT(i);
    }
    pq->A[i] = val;
    return;
}

// per estrarre l'elemento a massima priorita' mi basta prendere il primo elemento del
// vettore, scambiarlo con l'ultimo e ridurre la dimesione della heap
// infine applico la HEAPify per ripristinare la heap con ragionamento uguale allo HEAPsort
// T(n) = O(logn)
Item PQextractMax (PQ pq) {
    Item val;
    val = pq->A[0];
    swap(pq->A, 0, pq->heapsize--);
    // HEAPify(pq, 0); bisognerebbe sistemare i tipi
    return val;
}

// devo cercare l'elemento di cui voglio cambiare la priorita' (la key in questo caso)
// quindi cerco grazie alle funzioni di interfaccia NAME
// se ho trovato l'elemento
void PQchange(PQ pq, Item val) {
    int i, found = 0, pos;
    for(i = 0; i < pq->heapsize && found == 0; i++)
    if (NAMEcmp(NAMEget(&(pq->A[i])),NAMEget(&val)) == 0) {
        found = 1;
        pos = 1;
    }
    if (found==1) {
        // ora uso il while di PQinsert per fare risalire l'elemento
        // nella posizione giusta declassando gli eventuali padri
        while (pos >= 1 &&
               KEYget(pq->A[PARENT(pos)]) < KEYget(val)) {
            pq->A[pos] = pq ->A[PARENT(pos)];
            pos = PARENT(pos);
        }
        pq->A[pos] = val;
        // applico una HEAPify in caso ho fatto scambi anche se non li ho fatti
        // vabbe
        HEAPify(pq, pos);
    } else
        printf("key not found!\n");
}