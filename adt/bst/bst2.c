#include "bst.h"
#include "../item.h"
#include <stdlib.h>

// in questa implementazione del bst aggiungiamo il puntatore al padre
// e il numero di nodi che e' radicato nel nodo corrente

typedef struct BSTnode* link;
struct BSTnode {
    Item item;
    link p; link l; link r;
    int N;
};
struct binarysearchtree {link root; link z;};

static link NEW(Item item, link p, link l, link r, int N) {
    link x = (struct BSTnode*) malloc(sizeof (struct BSTnode));
    x->item = item;
    x->p = p; x->l = l; x->r = r; x->N = N;
    return x;
}

BST BSTinit() {
    BST bst = malloc(sizeof *bst);
    bst->root = (bst->z = NEW(ITEMsetNull(), NULL, NULL, NULL, 0));
    return bst;
}

Item minR(link h, link z);

// una funzione che non avevamo implementato prima perche' sarebbe stato
// troppo complesso senza il padre
// 2 casi per trovare il successore (item appena maggiore del nodo considerato)
// 1) se il nodo corrente ha un sotto albero destro allora si tratta di trovare il
// minimo di quel sotto albero
// 2) se il nodo corrente non ha un sotto albero destro allora si tratta di
// trovare il primo antenato da cui si scende verso sinistra
Item searchSucc(link h, Key k, link z) {
    // abbiamo prima una parte di ricerca del nodo
    // con ricorsione ma quello che importa e' l'algoritmo
    // quando abbiamo trovare il nodo
    link p;
    if (h == z) return ITEMsetNull();
    if (KEYcompare(k, KEYget(h->item)) == 0) {
        if (h->r != z)  // caso 1)
            return minR(h->r, z);
        else {  // caso 2)
            p = h->p;
            // scorro in alto finche' h e' un figlio destro
            // perche' devo trovare il primo figlio da sinistra
            while(p != z && h == p->r)
                h = p; p = p->p;
            return p->item;
        }
    }
    if (KEYcompare(k, KEYget(h->item)) == -1)
        return searchSucc(h->l, k, z);
    return searchSucc(h->r, k, z);
}

Item BSTsucc(BST bst, Key k) {
    return searchSucc(bst->root, k, bst->z);
}

Item maxR(link h, link z);

// come prima 2 casi
// 1) il massimo del sotto albero di sinistra del nodo corrente
// 2) il primo antenato tale che si scende verso destra
Item searchPred(link h, Key k, link z) {
    link p;
    if (h == z) return ITEMsetNull();
    if (KEYcompare(k, KEYget(h->item)) == 0) {
        if (h->l != z)
            return maxR(h, z);
        p = h->p;
        while (p != z && p->l == h) {
            h = p; p = p->p;
        }
        return p->item;
    }
    if (KEYcompare(k, KEYget(h->item)) == 1)
        return searchPred(h->r, k, z);
    return searchPred(h->l, k, z);
}

Item BSTpred(BST bst, Key key) {
    return searchPred(bst->root, key, bst->z);
}

// modifiche semplici nella funzione insertR
link insertR(link h, Item x, link z) {
    int cmp;
    if (h == z)
        return NEW(x, z, z, z, 1);
    cmp = KEYcompare(KEYget(x), KEYget(h->item));
    if (cmp == 1) {
        h->r = insertR(h->r, x, z);
        h->r->p = h;    // setto correttamente il padre
    } else {
        h->l = insertR(h->l, x, z);
        h->l->p = h;    // setto il padre
    }
    (h->N)++;   // incremento perche' ho aggiunto un nodo
    return h;
}

// BSTselect
// selezione dell'item con la r-esima chiave piu' piccola (r = rango
// cioe' la chiave in posizione r nell'ordinamento, es. se r = 0
// si tratta della chiave piu' piccola, = 1 la penultima piu' piccola ecc.)
// considero t = # di nodi del sotto albero sinistro
// 1) t = r ritorno la radice del sotto albero
// 2) t > r ricorsione nel sotto albero sinistro alla ricerca
// della k-esima chiave piu' piccola
// 3) t < r ridorsione nel sottoalbero destro alla ricerca della
// (r-t-1)-esima chiave piu' piccola
// NOTA: si potrebbe tranquillamente fare una visita in order e poi fermarsi
// una volta trovare la chiave con la proprieta' desiderata ma sarebbe lineare
// invece vogliamo un algoritmo che e'
Item selectR(link h, int r, link z) {
    int t;
    if (h == z)
        return ITEMsetNull();
    t = h->l->N;
    if (t > r)
        return selectR(h->l, r, z);
    if (t < r)
        return selectR(h->r, r-t-1, z);
    return h->item;
}

Item BSTselect(BST bst, int r) {
    return selectR(bst->root, r, bst->z);
}

link rotR(link h);
link rotL(link h);

// partizionare significa selezionare una chiave e poi farla risalire in radice
link partR(link h, int r) {
    int t = h->l->N;
    if (t > r) {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r) {
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}

// cancellare un nodo con chiave k signfica
// 1) rimpiazzarlo con predecessore/successore se e' radice di un sottoalbero
// 2) cancellarlo e basta se e' una foglia
// per il caso 1) posso usare partR
link joinLR(link a, link b, link z) {
    if (b == z)
        return a;
    // caso 1)
    b = partR(b, 0);    // faccio risalire il predecessore (ha rango 0 perche' e' il minimo del sotto albero)
    // parte di roazione
    b->l = a;
    a->p = b;
    b->N = a->N + b->r->N +1;
    return b;
}

link deleteR(link h, Key k, link z) {
    link y, p;
    if (h == z) return z;
    if (KEYcompare(k, KEYget(h->item)) == -1)
        h->l = deleteR(h->l, k, z);
    if (KEYcompare(k, KEYget(h->item)) == 1)
        h->r = deleteR(h->r, k, z);
    (h->N)--;
    if (KEYcompare(k, KEYget(h->item)) == 0) {
        y = h; p = h->p;
        h = joinLR(h->l, h->r, z); h->p = p;
        free(y);
    }
    return h;
}

void BSTdelete(BST bst, Key k) {
    bst->root = deleteR(bst->root, k, bst->z);
}

// per bilianciare un albero usiamo l'algoritmo di fare
// un partizionamento a destra e a sinistra della chiave mediana
// (chiave che ha il rango che sta a meta' tra 0 e N) e dei 2 sotto alberi
static link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    r = (h->N+1)/2 - 1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}

void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}

// come si sviluppa una nuova struttura dati? proviamo
// a estendere una struttura dati esistente ad esempio il bst
// aggiungendo nuove informazioni (dimensione del sotto albero)
// verificando di mantenere queste nuove informazioni senza alterare la
// complessita' delle operazioni esistenti
// e sviluppando nuove operazioni (es. BSTselect)
// questo era l'order-statistic bst

// con lo stesso ragionamento sviluppiamo l'interval BST
// la chiave e' un intervallo e non un solo valore
// che puo' essere rappresentato come valori int low e high nella struct Item
// in ogni nodo del ibst memorizziamo il massimo del suo sottoalbero
// tutte le funzioni non cambiano oppure sono leggermente modificate per gestire le
// nuove informazioni fatta eccezione per la BSTselect perche' ora dobbiamo cercare un intervallo
// che interseca uno di quelli dei nodi




