// peso del cammino = somma dei pesi di tutti gli archi che attraversa il cammino
// noi vogliamo calcolare i cammini minimi da sorgente singola
// e cioe' il cammino minimo e il suo peso da un vertice s a ogni altro vertice v
// ci sono due algoritmi: dijkstra e bellman-ford

// archi a peso negativo (senza ciclo a peso < 0):
// 1) algoritmo di dijkstra, soluzione ottima non garantita
// 2) algoritmo di bellman-ford, soluzione ottima garantita
// esiste un ciclo a peso negativo: il problema non ha piu' senso

// i cammini minimi non possono contenere neanche cicli a peso positivo
// e quindi sono semplici e posso contenere al massimo |V| - 1 archi
// dove |V| e' il numero di vertici del grafo

// si potrebbe risolvere il problema con un approccio brute-force con i modelli del calcolo combinatorio

// si tratta di un problema di ottimizzazione quindi proviamo con programmazione dinamica o greedy
// lemma: un sottocammino di un cammino minimo e' un cammino minimo
// quindi il problema ha una sottostruttura ottima

// rappresentazione dei cammini minimi
// 1) vettore dei predecessori st[v] che contiene il parent di v (in st[v])
// 2) sottografo dei predecessori che ha come vertici s (vertice di partenza)
//    e v se st[v] != -1 e come archi (st[v], v) se v appartiene all'insieme dei vertici - il vertice s
// 3) albero dei cammini minimi con V' vertici raggiungibili da s
//    s radice dell'albero
//    per ogni vertice v in V' l'unico cammino semplice da s a v nell'albero e'
//    un cammino minimo da s a v nel grafo originale

// relaxation: lasciare che una soluzione violi un vincolo temporaneamente e
// poi eliminare la violazione

// vettore d che contiene una stima (limite superiore) del cammino minimo per raggiungere il nodo a ogni indice
// all'inizio st[v] = -1 e d[v] = max, suppongo che ho raggiunto v con un certo d[v]
// provo a rilassare per vedere se raggiungere v da passando da un altro vertice migliori
// la stima if (d[v] > d[u] + wt(u,v) allora d[v] = d[u] + wt(u,v); st[v] = u perche' miglioro la stima

// dijkstra applica il rilassamento una volta ad ogni arco mentre bellman-ford piu' volte

// algoritmo di dijkstra
// strategia greedy (assenza di archi a peso negativo garantisce comunque la soluzione ottima)
// S: e' l'insieme dei vertici il cui cammino minimo e' gia' determinato a partire dal vertice di partenza s
// V-S: e' una coda a priorita' PQ dei vertici ancora da stimare
// termina quando PQ e' vuota
// estrae u da V-S (dove d[u] e' il minimo, caratteristica greedy)
// inserisce in S
// rilassa tutti gli archi uscenti da u

#include "graph.h"
#include <stdlib.h>
#include "../priorityqueue/PQ.h"
#include "../item.h"
#include "../tabelledihash/ST.h"

typedef struct node* link;

struct graph {int V; int E; link* ladj; ST tab; link z};

struct node {
    int wt;
    int v;
    link next;
};  // nodo della lista delle adiacenze

static int maxWT = 1000000;

void GRAPHspD(Graph G, int id) {
    int v;
    link t;
    // definisco le varie strutture dati
    PQ pq = PQinit(G->V);
    int *st, *d;
    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));
    // inizializzo i valori di st e d
    for (v = 0; v < G->V; v++) {
        st[v] = -1;
        d[v] = maxWT;
        //PQinsert(pq, d, v)
    }
    // nodo di partenza s
    d[id] = 0;
    st[id] = id;
    //PQchange(pq, d, id); serve a riaggiornare la priorita' di d[id] e st[id]
    while (!PQempty(pq)) {  // finche la coda non e' vuota
        //if (d[v = PQextractMin(pq, d)] != maxWT)
            for (t = G->ladj[v]; t != G->z; t=t->next)  // per ogni nodo nella lista delle adiacenze
                if (d[v] + t->wt < d[t->v]) {   // se per andare da t->v mi conviene passare da v e aggiungere il peso dell'arco (u,v) relaxation
                    // aggiorno vettore padri e stima distanza
                    d[t->v] = d[v] + t->wt;
                    st[t->v] = v;
                    //PQchange(pq, d, t->v);
                }
    }
    // visualizzo i risultati
}

// se applico dijkstra a un dag mi basta ordinarlo topologicamente
// e poi applicare la relaxation a ogni arco uscente da ogni nodo seguendo il suddetto ordinamento

// un applicazione dei cammini minimi e' il seam carving: un algoritmo di compressione di immagini
// che non produce notevoli distorsioni

// trattiamo il problema dei cammini massimi sui dag
// in un grafo qualsiasi si tratta di un problema intrattabile
// in un dag:
// 1) ordinamento topologico
// 2) per ogni vertice ordinato applico una relaxation "inversa"
// nota: i valori iniziali non sono piu maxWt = inf ma -inf ovviamente

// algoritmo di bellman-ford
// strategia programmazione dinamica
// possono esserci archi a peso negativo ed e' garantita la soluzione ottima
// e' anche in grado di inviduare cicli a peso negativo
// sappiamo che un cammino e' al massimo costituito da |V| - 1 archi (altrimenti ci sono cicli)
// partiamo da una soluzione ricorsiva
// d0(v) e' la distanza dal vertice di partenza 0 a un generico vertice v
// che vale 0 se v = s altrimenti maxWt
// consideriamo la generica dw(v) distanza da un vertice di partenza w al generico vertice v
// questa e' il minimo tra se stessa e la distanza dw-1(u) + wt(u,v) dove u e' uno dei
// vertice su cui insiste un arco uscente verso v

// soluzione iterativa
// vettori d e st inizializzati
// |V| - 1 passi
// al passo i-esimo: rilassamento sugli archi in avanti
// al |V|-esimo passo: se diminuisce almeno una stima esiste un ciclo < 0 altrimenti soluzione ottima
// se ci si accorge che le stime non cambiano da un passo all'altro del ciclo ci si puo' anche fermare

// dobbiamo scegliere un ordine degli archi su cui applicare ogni passo del ciclo
// possiamo scegliere ad esempio un ordine lessicografico

void GRAPHspBF(Graph G, int id) {
    int v, i, negcycfound;
    link t;
    int *st, *d;
    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));
    for (v = 0; v < G->V; v++) {
        st[v] = -1;
        d[v] = maxWT;
    }
    d[id] = 0;
    st[id] = id;
    for (i = 0; i < G->V-1; i++)
        for (v = 0; v < G->V; v++)
            if (d[v] < maxWT)
                for (t = G->ladj[v]; t != G->z; t = t->next)
                    if (d[t->v] > d[v] + t->wt) {
                        d[t->v] = d[v] + t->wt;
                        st[t->v] = v;
                    }
    negcycfound = 0;
    for (v = 0; v < G->V; v++)
        if (d[v] < maxWT)
            // ladj[v] ritorna la lista dei vertici adiacenti a v significa che sono tutti archi
            // del tipo (v, x) dove x sono i vertici che appartengono a ladj[v]
            for (t = G->ladj[v]; t != G->z; t = t->next)
                // t->v e' quindi uno di questi vertici x
                // vediamo se conviene mantenere la distanza corrente d[t->v]
                // oppure usare la distanza trovata per il vertice v di partenza piu' il peso dell'arco
                // questo per ogni membro della lista delle adiacenze (for loop con t)
                if (d[t->v] > d[v] + t->wt)
                    negcycfound = 1;
    if (negcycfound == 0)
        // stampa soluzione
        printf("soluzione");
    else
        printf("trovato ciclo negativo!")
}