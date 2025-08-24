#include "graph.h"
#include "../tabelledihash/st.h"
#include <stdlib.h>

typedef struct node* link;
struct node {
    link next;
    int v;
    int wt; 
};

struct graph {
    link *ladj;
    int V;
    int E;
    link z;
    ST tab;
};

Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

// recursive function
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

// **Breadth-First Search (BFS)**
// - Determines all vertices reachable from `s`, meaning it does not necessarily visit all vertices in the graph.
// - Computes the minimum distance from `s` to all adjacent vertices.
// - Uses a `dist` array for this purpose.
// - Utilizes a queue.
// - Initially inserts a dummy edge for node `id`.
// - While the queue is not empty:
//   - Extract an edge `(v, w)`, and if `w` is a white (unvisited) vertex:
//     - Update `st`, `pre` for that vertex and insert into the queue the edges connecting `w` to its adjacent and white vertices.

// Wrapper function with a simple dummy edge (calls the recursive function only once, unlike DFS, which does so in a loop).

// Recursive function
void bfs(Graph G, Edge e, int *time, int *pre, int *st) {
    if (e.v != e.w)
        printf("(%d, %d)", e.v, e.w); // Can print the edges as they are discovered
    // Q q;
    // q = Qinit();
    // Qput(q, e); // Insert edge into the queue
    // dist[e.v] = -1; // Dummy edge, distance from `s` = -1
    // while (!Qempty(q))
    // if (pre[(e = Qget(q)).w] == -1) {
    // pre[e.w] = (*time)++;
    // st[e.w] = e.v;
    // dist[e.w] = dist[e.v] + 1; // The well-known minimum distance
    // for (x = 0; x < G->V; x++) {
    // if (G->madj[e.w][x] == 1) // Adjacency matrix: check if edge `(w, x)` exists, where `x` iterates over all vertices
    // if (pre[x] == -1) // If not yet processed
    // Qput(q, EDGEcreate(e.w, x)); // Add edge to the queue
}
