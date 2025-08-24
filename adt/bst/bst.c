#include "bst.h"
#include <stdlib.h>

#define PREORDER -1
#define INORDER 0
#define POSTORDER 1

// si tratta di alberi binari dove il nodo di sinistra (left) e' minore
// della radice e il nodo di destra (right) e' maggiore della radice

typedef struct BSTnode* link;
struct BSTnode {
    Item item;
    link l;
    link r;
};
struct binarysearchtree {
    link root;
    link z; // nodo fittizio per dire che il bst e' vuoto
};

static link NEW(Item item, link l, link r) {
    link x = malloc(sizeof (*x));
    x->item = item;
    x->l = l;
    x->r = r;
}

BST BSTinit() {
    BST bst = malloc(sizeof(*bst));
    bst->root = (bst->z = NEW(ITEMsetNull(), NULL, NULL));
    return bst;
}

// helper
static void treeFree(link h, link z) {
    if (h == z) // equivale nelle liste ad h == NULL
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

void BSTfree(BST bst) {
    if (bst == NULL)
        treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}

// helper
static int countR(link h, link z) {
    if (h == z)
        return 0;
    return countR(h->l, z) + countR(h->r, z) + 1;
}

int BSTcount(BST bst) {
    return countR(bst->root, bst->z);
}

int BSTempty(BST bst) {
    if (BSTcount(bst) == 0)
        return 1;
    return 0;
}

static Item searchR(link h, Key k, link z) {
    int cmp;
    if (h == z)
        return ITEMsetNull();
    cmp = KEYcompare(KEYget(h->item), k);
    if (cmp == 0)
        return h->item;
    if (cmp == 1)
        return searchR(h->r, k, z);
    if (cmp == -1)
        return searchR(h->l, k, z);
}

Item BSTsearch(BST bst, Key k) {
    return searchR(bst->root, k, bst->z);
}

static Item minR(link h, link z) {
    if (h == z)
        return ITEMsetNull();
    if (h->l == z)
        return (h->item);
    return minR(h->l, z);
}

Item BSTmin(BST bst) {
    return minR(bst->root, bst->z);
}

Item maxR(link h, link z) {
    if (h == z)
        return ITEMsetNull();
    if (h->r == z)
        return h->item;
    return maxR(h->r, z);
}

Item BSTmax(BST bst) {
    return maxR(bst->root, bst->z);
}

static link insertR(link h, Item x, link z) {
    int cmp;
    if (h == z)
        return NEW(x, z, z);
    cmp = KEYcompare(KEYget(x), KEYget(h->item));
    if (cmp == 1)
        // queste assegnazioni servono a preservare la struttura dell'abero
        // se mi trovo in un nodo foglia e ho inserito cosi' sono sicuro che
        // il padre punti al nuovo nodo appena inserito
        h->r = insertR(h->r, x, z);
    else
        h->l = insertR(h->l, x, z);
    return h;
}

// T(n) compreso tra O(logn) e O(n)
// dipende se l'albero e' completamente sbilanciato (degenera in una lista)
// oppure se e' completo o quasi completo
void BSTinsert_leafR(BST bst, Item x) {
    bst->root = insertR(bst->root, x, bst->z);
}

void BSTinsert_leafI(BST bst, Item x);

// stampando in order l'albero grazie alle proprieta' del bst
// ottengo la stampa di tutte le chiavi in ordinamento crescente
void treePrintR(link h, link z, int strategy) {
    if (h == z)
        return;
    if (strategy == PREORDER)
        ITEMshow(h->item);
    treePrintR(h->l, z, strategy);
    if (strategy == INORDER)
        ITEMshow(h->item);
    treePrintR(h->r, z, strategy);
    if (strategy == POSTORDER)
        ITEMshow(h->item);
}

void BSTvisit(BST bst, int strategy) {
    if (BSTempty(bst))
        return;
    treePrintR(bst->root, bst->z, strategy);
}

link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}

link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

link insertT(link h, Item x, link z) {
    if (h == z)
        return NEW(x, z, z);
    if (KEYcompare(KEYget(x), KEYget(h->item)) == -1) {
        h->l = insertT(h->l, x, z);
        // le rotazioni sono opposte a dove si scende (scendo a sinistra ruoto a destra..)
        // prima inserisco in foglia poi nel backtracking faccio risalire il nodo appena inserito
        // usando le operazioni di rotazione
        h = rotR(h);
    } else {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
    }
    return h;
}

// inserisco in foglia e faccio risalire con le rotazioni
void BSTinsert_root(BST bst, Item x) {
    bst->root = insertT(bst->root, x, bst->z);
}
