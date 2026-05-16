#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Edge {
    int neighbor;
    // next edge out of a vertex
    struct Edge *next;
} Edge;

typedef struct {
    Edge** adj_list;
    char** labels;
    size_t num_vertices;
    size_t num_edges;
} Graph;



Graph* init_graph(int vertices);
void free_graph(Graph* g);
bool add_edge(Graph* g, int src, int dest);
bool remove_edge(Graph* g, int src, int dest);


void print_graph(Graph* g);
int degree(Graph* g, int v);
int total_degree(Graph* g);

bool is_connected(Graph* g);
bool is_eulerian(Graph* g);

void hierholzer(Graph*g, int src);



#endif
