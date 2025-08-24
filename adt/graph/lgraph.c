#include "graph.h"
#include <stdlib.h>

// implemented with adjacency list

typedef struct node* link;
struct node {
    link next;
    int v;  // vertex where the arrow points to
    int wt;
}

struct graph {
    int V;
    int E;
    link* ladj; // each list ladj[i] contains the nodes to which the node i is connected to
    link v;     // if the graph is indirected if the edge is i-j, i is present in ladj[j] and j in ladj[i]
    ST tab;     // the weight may or may not be included depending if the graph is weigthed or not
};

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof(*x));
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

Graph GRAPHinit(int V) {
    Graph G;
    G->E = 0;
    G->V = V;
    G->z = NEW(-1, -1, NULL);
    G->ladj = malloc(G->V * sizeof(link));
    for (int v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    return G;
}

void GRAPHfree(Graph G) {
    for (int v = 0; v < G->V; v++) {
        for (link t = G->ladj[v]; t != G->z; ) {
            link x = t;
            t = t->next
            free(x)
        }
    }
    free(G->ladj);
    STfree(G->tab);
    free(G->z);
    free(G);
}

void GRAPHload(FILE *fin) {
}

void GRAPHstore(Graph G, FILE *fout) {
}

int GRAPHgetIndex(Graph G, char* label) {
    return -1;
}

void GRAPHinsertE(Graph G, int v, int w, int wt) {
    G->ladj[v] = NEW(G->ladj[v], w, wt);
    //G->ladj[w] = NEW(G->ladj[w], v, wt); // add this line if the graph is indirected
    G->E++;
}

static void LISTremove(Graph G, link head, int w) {
    if (head == G->z)
        return;
    if (head->w == w) {
        // remove from head
        link t = head;    // don't leak memory
        head = t->next;
        free(t);
        G->E--;
        return;
    }
    // remove in between
    link p, x;
    for (p = head, x = p->next; x != G->z; p = x, x = x->next) {
        if (x->w == w) {
            p->next = x->next;
            free(x);
            G->E--;
            return;
        }
    }
}

void GRAPHremoveE(Graph G, int v, int w) {
    LISTremove(G, G->ladj[v], w);
    // LISTremove(G, G->ladj[w], v);
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

void GRAPHedges(Graph G, Edge *a) {
    int E = 0;
    for (int v = 0; v < G->V; v++) {
        for (link x = G->ladj[v]; x != G->z; x = x->next) {
            // if (x->v > v) { // wrap in this if statement if the graph is indirected (just like matrix j > i)
            Edge e = EDGEcreate(v, x->v, x->wt);
            a[E++] = e;
            //}
        }
    }
}

int pathR(Graph G, int v, int w, int* visited) {
    if (v == w)
        return 1;
    visisted[v] = 1;
    for (link x = G->ladj[v]; x != G->z; x = x->next) {
        if (visited[x->v] == 0) {
            // if (x->v > v) { // wrap in this if statement if the graph is indirected (just like matrix j > i)
            if (pathR(G, x->w, w, visited)) {
                printf("\n(%s %s) in path", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, x->w));
                return 1;
            }
            //}
        }
    }
    return 0;
}

void GRAPHpath(Graph G, int start, int end) {
    int* visited = calloc(G->V * sizeof(int));
    if (!pathR(G, start, end, visited))
        printf("\n path not found! \n");
    free(visited);
    return;
}

void GRAPHbfs(Graph G, int A) {
}

static void dfsR(Graph G, Edge e, int *time, int* pre, int *post, int* st) {
    link t;
    int v, w = e.w;
    Edge x;
        // print TREE edge found during recursion, excluding the dummy edge
    if (e.v != e.w)
        printf("(%s, %s) TREE edge", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w)); 
    st[w] = e.v;
    pre[w] = (*time)++;  // update parent and `pre` array for `w`
    for (t = G->ladj[w]; t != G->z; t = t->next)f
        if (pre[t->v] == -1)    // if node `v` in edge `(w, v)` has not been discovered, continue search
            dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
        else {
            // Edge classification: BACK, FORWARD, and CROSS
            v = t->v;
            // edge (w, v)
            if (pre[w] > pre[v])    // If `v` was discovered before `w` in edge `(w, v)`, `v` is an ancestor of `w`
                printf("(%d, %d) BACK edge", w, v);
            // This would be sufficient for undirected graphs.
            // From here onward, it applies to directed graphs.
            if (post[v] == -1)
                printf("(%d, %d) BACK edge", w, v); // Similar to before: a back edge if `v` has not yet finished processing, meaning `v` is necessarily an ancestor
            else {
                if (pre[w] < pre[v])
                    printf("(%d, %d) FORWARD edge", w, v); // Opposite reasoning: if `w` was discovered before `v`, `w` is an ancestor and `v` is its child
                else
                    printf("(%d, %d) CROSS edge", w, v); // By elimination
            }
        }
    post[w] = (*time)++;
}

// wrapper function
void dfs(Graph G, int id) {
    // `id` is the starting node on which a dummy edge is created
    // initialize variables
    int v, time = 0, *pre, *post, *st;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));    // fathers' vector
    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }
    // First DFS call with dummy edge from the starting node
    dfsR(G, EDGEcreate(id, id), &time, pre, post, st);
    // Loop to ensure the entire graph is visited, even if it is not connected
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR(G, EDGEcreate(v, v), &time, pre, post, st);
    printf("discovering/endprocessing time labels\n");
    for (v = 0; v < G->V; v++) {
        printf("%s: %d %d", STsearchByIndex(G->tab, v), pre[v], post[v]);
    }
    printf("resulting dfs tree");
    for (v = 0; v < G->V; v++) {
        printf("%s's parent: %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
    }
}

static void dfsccR(Graph G, int* cc, int v, int id) {
    cc[v] = id;
    for (link x = G->ladj[v]; x != NULL; x = x->next) {
        if (cc[x->v] == -1) {
            // (v, x->v)
            dfsccR(G, cc, v, id);
        }
    }
}

// connected components, undirected graphs
void GRAPHcc(Graph G) {
    int* cc = malloc(G->V * sizeof(int));
    for (int i = 0; i < G->V; i++)
        cc[i] = -1;
    int id = 0;
    for (int i = 0; i < G->V; i++) {
        if (cc[i] == -1) {
            dfsccR(G, cc, i, id++);
        }
    }
}

// strongly connectec components for directed graphs, kosaraju algorithm
void GRAPHscc(Graph G) {
    
}
