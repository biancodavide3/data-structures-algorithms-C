// abbiamo bisogno di un albero binario (ogni nodo ha al massimo due figli) quasi completo
// (ogni livello e' completo cioe' non mancano nodi tranne nell'ultimo, dove mancano nodi
// a partire da destra in maniera consecutiva, senza lasciare buchi, questa e' una proprieta'
// strutturale) con la proprieta' funzionale ogni parent sia maggiore di tutti i suoi figli.
// ora rappresentiamo questo albero particolare come vettore "enumerandolo partendo
// dall'alto fino all'ultimo livello da sinistra verso destra", la relazione rigorosa e' che
// se il parent si trova alla posizione i il figlio sinistro e' alla posizione LEFT(i)=2i+1 e quello destro
// alla posizione RIGHT(i)=2i+2, il parent dato un figlio alla posizione i e' PARENT(i)=(i-1)/2

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct heap {
    Item *A;
    int heapsize;   // contiene quanto e' grande l'heap in ogni momento
};

int LEFT(int i) {
    return 2 * i + 1;
}

int RIGHT (int i) {
    return 2 * i + 2;
}

int PARENT(int i) {
    return (i - 1) / 2;
}

Heap HEAPinit(int maxN) {   // la dimensione massima del vettore dell'heap
    Heap h;
    h = (struct heap*) malloc(sizeof (struct heap));
    h->A = malloc(maxN * sizeof(Item));
    h->heapsize = 0;
    return h;
}

void HEAPfree(Heap h) {
    free(h->A);
    free(h);
}

// aggiunge un elemento alla heap senza pero' garantire la proprieta' funzionale
// del padre sempre maggiore dei figli
void HEAPfill(Heap h, Item item) {
    int i;
    i = h->heapsize++;
    h->A[i] = item;
}

void HEAPdisplay(Heap h) {
    int i;
    for (i = 0; i < h->heapsize; i++)
        ITEMshow(h->A[i]);
}

// questa funzione permette di trasformare in heap un albero
// dove scegliendo un parent in posizione i gli alberi dei suoi figli
// rispettano gia' la proprita' funzionale dell'heap ma il parent no
// quindi prendo il figlio piu' grande e lo swappo col parent e ricorsivamente
// faccio la stessa cosa finche' non si propaga il cambiamento fino alla base
// es.
//          16
//        4  10
//      14  7  9  3
//     2 8 1
// scambio 14 con 4 e poi il 4 con l'8 e ho la struttura dell'heap
// T(n) = log(n)
void HEAPify(Heap h, int i) {
    int largest = i;
    int l = LEFT(i);
    int r = RIGHT(i);
    if (l < h->heapsize && KEYcompare(KEYget(h->A[l]), KEYget(h->A[largest]) > 0))
        largest = l;
    if (r < h->heapsize && KEYcompare(KEYget(h->A[r]), KEYget(h->A[largest]) > 0))
        largest = r;
    if (largest != i) {
        swap(h->A, i, largest);
        HEAPify(h, largest);
    }
}

// posso usare HEAPify per trasformare un qualsiasi albero binario in un heap
// mettendo a posto ogni parent partendo dal parent dell'ultimo nodo nell'ultimo livello
// posso farlo perche' alla prima chiamata i figli del parent (i nodi dell'ultimo livello
// non hanno figli e quindi rispettano sicuro la proprieta' funzionale) e poi a salire perche'
// so che la HEAPify ritornera' sotto alberi che rispettano la proprieta' funzionale
// T(n) = O(n) e NON O(nlogn) come si potrebbe pensare
// attenzione a fare analisi a vista se non si e' sicuri
void HEAPbuild(Heap h) {
    int i;
    for (i = PARENT(h->heapsize -1); i >= 0; i--)
        HEAPify(h, i);
}

// possiamo realizzare una funzione di ordinamento di un vettore
// perche' sappiamo che il primo elemento dello heap e' il piu' grande di tutti
// quindi dato un vettore
// 1) lo trasformo in heap con HEAPbuild
// 2) scambio il primo con l'ultimo elemento
// 3) riduco la dimensione dell'heap di 1
// 4) ripristino la proprieta' dell'heap
// 5) ripeto i passaggi 1-4 fino a quando non ho esaurito l'heap
// T(n) = O(nlogn), in loco, non stabile
void HEAPsort(Heap h) {
    int i, j;
    HEAPbuild(h);
    j = h->heapsize;
    for (i = h->heapsize-1; i >= 0; i--) {
        swap(h->A, 0, i);
        h->heapsize--;
        HEAPify(h, 0);
    }
    h->heapsize = j;
}



