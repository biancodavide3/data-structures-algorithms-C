```c
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