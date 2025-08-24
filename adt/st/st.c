// These are data structures with an average access time complexity of O(1)
// Thanks to a hash function, the search key is transformed into a search index,
// but this function cannot be perfect and leads to collisions,
// meaning that two different entries attempt to access the same slot.

// They do not support sorting and selection, only insertion, search, and deletion.

// From now on, we assume that the hash function is given.

// Linear chaining
// The linear chaining method for handling collisions consists of using linked lists.

#include "st.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct STnode* link;

struct STnode { Item item; link next; };

// N = number of currently stored values
// M = number of slots in the array (i.e., the number of lists or
// the size of the heads array)
struct symtab { link *heads; int N; int M; link z; };

static link NEW(Item item, link next) {
    link x;
    x = (link) malloc(sizeof(link*));
    x->item = item;
    x->next = next;
    return x;
}

// maxN is the maximum number of items in the table
// r is a reasonable expected average length for the lists
static int STsizeSet(int maxN, float r) {
    int primes[16] = {2,3,5,7,11,13,
                      17,19,23,29,31,
                      37,41,43,47,53};
    int i = 0;
    int size;
    size = maxN / r;
    if (size < primes[15]) {
        for (i = 0; i < 16; i++)
            if (size <= primes[i])
                return primes[i];
    } else
        printf("Too many entries!\n");
    return -1;
}

ST STinit(int maxN, float r) {
    int i;
    ST st;
    st = malloc(sizeof(*st));
    st->N = 0;
    st->M = STsizeSet(maxN, r);
    st->heads = malloc(st->M*sizeof(link));
    st->z = NEW(ITEMsetNull(), NULL);
    for (i = 0; i < st->M; i++)
        st->heads[i] = st->z;
    return st;
}

void STfree(ST st) {
    int i;
    link t, u;
    for (i = 0; i < st->M; i++)
        for (t = st->heads[i]; t != st->z; t = u) {
            u = t->next;
            free(t);
        }
    free(st->z);
    free(st->heads);
    free(st);
}

int STcount(ST st) { return st->N; }

int STempty(ST st) {
    if (STcount(st) == 0)
        return 1;
    return 0;
}

static int hash(Key v, int M);
static int hashU(Key v, int M); 
// A variant of the hash function where a parameter changes
// for each character in the key (in this case, the key is a string)

void STinsert(ST st, Item val) {
    int i;
    i = hash(KEYget(val), st->M);
    st->heads[i] = NEW(val, st->heads[i]);
}

// Recursive search in linked lists
Item searchR(link t, Key k, link z) {
    if (t == z) return ITEMsetNull();
    if ((KEYcompare(KEYget(t->item), k)) == 0) return t->item;
    return searchR(t->next, k, z);
}

// We only need to search in the list corresponding to the hash of the key
Item STsearch(ST st, Key k) {
    return searchR(st->heads[hash(k, st->M)], k, st->z);
}

// Recursive deletion in linked lists
link deleteR(link x, Key k) {
    if (x == NULL) return NULL;
    if ((KEYcompare(k, KEYget(x->item))) == 0) {
        link t = x->next;
        free(x);
        return t;
    }
    x->next = deleteR(x->next, k);
    return x;
}

// We only need to delete from the list corresponding to the hash of the key
void STdelete(ST st, Key k) {
    int i = hash(k, st->M);
    st->heads[i] = deleteR(st->heads[i], k);
}

// Recursive list traversal
void visitR(link h, link z) {
    if (h == z) return;
    ITEMshow(h->item);
    visitR(h->next, z);
}

// No ordering is present in this traversal
void STdisplay(ST st) {
    int i;
    for (i = 0; i < st->M; i++)
        visitR(st->heads[i], st->z);
}

// Complexity:
// Hash functions have constant cost, and complexity depends only on the list lengths.
// We define the load factor α = N/M, which could even be less than 1
// (meaning there are more lists than elements).
// - Insertion: T(n) = O(1)
// - Worst-case search: T(n) = θ(N), average case: T(n) = O(1 + α)
// - Deletion: Same as search, unless the list is doubly linked.
