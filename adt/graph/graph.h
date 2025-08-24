#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

// Easy graph problems

// Determine if a graph is connected
// Determine the presence of a cycle
// Identify strongly connected components
// Find minimum spanning trees
// Calculate shortest paths
// Determine if a graph is bipartite
// Find an Eulerian path

// Difficult graph problems

// Hamiltonian cycle problem

// Coloring problem
// Given an undirected graph, what is the minimum number of
// colors k required such that no vertex has the same color
// as an adjacent vertex?

// Another intractable problem is the longest path problem

// How to represent a graph? Adjacency matrix, adjacency list, edge list

// Definitions:
// Let's write an undirected graph G = (V, E) where V is the set of vertices and E is the set of edges
// (the connections between vertices) either ordered or not
// A graph is said to be directed if its edges have a specific direction
// A graph is said to be weighted when its edges are associated with a weight
// A connected component (for undirected graphs) is a set of vertices such that each
// vertex is reachable from another
// A strongly connected component (for directed graphs) is a set of vertices such that each vertex
// is reachable from another, respecting the direction of traversal
// Self-loop = edge (v, v)
// A tree is a special type of undirected graph where for n nodes there are n-1 edges,
// no cycles, and it is connected (any node can be reached from any other node),
// with a root node

// The most general model is the ADT of a directed and weighted graph, but we will introduce 4
// for each type (directed and weighted, undirected and weighted, directed and unweighted, undirected
// and unweighted)

// We also distinguish between static graphs (where vertices or edges are not added or removed),
// semi-static graphs (where vertices cannot be added or removed, but edges can),
// dynamic graphs (where vertices or edges can be added or removed)

// Here we consider only semi-static graphs where edges are logically deleted by adding
// a field to mark whether they are deleted or not

// For vertices, we use integers to identify them for the algorithm
// On the user side, they will have a name, so it's necessary to create a symbol table
// (either external or internal to the graph)
// Thus, we will have STsearch(char* name) that maps the name to the index
// and STsearchByIndex(int k) that maps the key to the name

// In this case, we use an internal symbol table within the graph ADT
// implemented as an unordered array with the vertex index coinciding with that of the array

// The number of vertices can be known by reading from a file
// or unknown but overestimated as twice the number of vertices

// Adjacency matrix
// This is a |V| x |V| matrix
// where the element is 1 if (i, j) belongs to E
// 0 otherwise

// If the graph is undirected, the matrix is symmetric
// If the graph is weighted, the element i,j is the weight or
// (instead of 1 or 0)
// Note: not necessarily all the diagonal elements are 0 (in directed graphs)

// Multigraphs: there is more than one edge connecting two vertices

// NOTE
// directed and weighted graph is the most complex type
// the others can be easily derived by simplifying functions
// there are some functions allowed only for specific graphs (e.g. cc and scc)
// for connected components and strongly connected components

typedef struct edge { int v; int w; int wt; } Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int V); // Initializes a graph with V vertices
void GRAPHfree(Graph G);
void GRAPHload(FILE *fin);
void GRAPHstore(Graph G, FILE *fout);
int GRAPHgetIndex(Graph G, char* label);

// Edge operations
void GRAPHinsertE(Graph G, int id1, int id2);  // Inserts an edge between id1 and id2
void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHedges(Graph G, Edge *a);  // List of edges, returned via a

// Path searching
int GRAPHpath(Graph G, int id1, int id2);  // Checks if a path exists between id1 and id2
void GRAPHpathH(Graph G, int id1, int id2); // Finds a Hamiltonian path for undirected graphs

// Graph traversal
void GRAPHbfs(Graph G, int id); // Breadth-first search
void GRAPHdfs(Graph G, int id); // Depth-first search

// Connected components
void GRAPHcc(Graph G);   // Connected components for undirected graphs
void GRAPHscc(Graph G);  // Strongly connected components for directed graphs

#endif // GRAPH_H
