#include "graph.h"
#include <stdlib.h>
#include "../symboltable/st.h"

// implemented with adjacency matrix

struct graph {
    int V;
    int E;
    int** madj; // madj[i][j] contains the weight of the edge between i and j (0 if not present)
    ST st;      // (or 1 if the graph is not weighted). If the graph is directed madj[j][i] may contain a different value
                // otherwise it has the same value as madj[i][j]
};

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

Graph GRAPHinit(int V) {
    Graph G;
    g->V = V;
    G->E = 0;
    G->madj = malloc(V * sizeof (int*));   // V * V
    G->st = STinit(V);
    for (int i = 0; i < G->V; i++)
        G->madj[i] = malloc(V * sizeof(int));
    for (int i = 0; i < G->V; i++)
        for (int j = 0; j < G->V; j++)
            G->madj[i][j] = 0;
    return G;
}

void GRAPHfree(Graph G) {
    for (int i = 0; i < G->V; i++)
        G->madj[]
}

void GRAPHload(FILE *fin) {
}

void GRAPHstore(Graph G, FILE *fout) {
}

int GRAPHgetIndex(Graph G, char* label) {
    return -1;
}

void GRAPHinsertE(Graph G, Edge e) {
    if (G == NULL)  
        return;
    if (G->madj[e.v][e.w] == 0) // we definitely added a new edge
        G->E++;
    G->madj[e.v][e.w] = e.wt;   // we might have just changed the weigth of an existing edge
    // G->madj[e.w][e.v] = e.wt; // add this line if the graph is indirected
    // set 1 instead of weight if you don't have a weight to indicate the present of an edge
}

void GRAPHremoveE(Graph G, Edge e) {
    if (G == NULL)
        return;
    if (G->madj[e.v][e.w] != 0)
        G->E--;
    G->madj[e.v][e.w] = 0;
    // G->madj[e.w][e.v] = 0; // add this line if the graph is indirected
}

// return the list of edges in vector a in any order
void GRAPHedges(Graph G, Edge *a) {
    if (G == NULL)
        return;
    int E = 0;
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {    // j should start from i + 1 if the graph is indirected (j > i)
            if (G->madj[i][j] != 0) {
                Edge e;
                e.v = i; e.w = j; e.wt = G->madj[i][j];
                a[E++] = e;
            } 
        }
    }
    return;
}
// find any path, no need to backtrack 
static int pathR(Graph G, int v, int w, int* visited) {
    if (v == w)
        return 1;
    
    visited[v] = 1;

    for (int i = 0; i < G->V; i++) {
        if (G->madj[v][i] != 0) {
            // if (i > v) { // wrap in this if statement is the graph is indirected
            if (visisted[i] == 0) {
                if (pathR(G, i, w, visited)) {
                    printf("(%d %d) in path\n", v, i);
                    return 1;
                }
            }
            //}
        }
    }
    return 0;
}

void GRAPHpath(Graph G, int id1, int id2) {
    int *visited = calloc(G->V*sizeof(int));
    int found = pathR(G, id1, id2, visited);
    if (found == 0)
        printf("\nPath not found!\n");
    return;
}

void GRAPHbfs(Graph G, int A) {

}

void GRAPHdfs(Graph G, int A) {
    
}

int GRAPHscc(Graph G) {
    return 0;
}

int GRAPHscc(Graph G) {
    return 0;
}


