#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

#define LABEL_SIZE 10


Graph* init_graph(int vertices) {
    Graph *g = malloc(sizeof(Graph));
    if (!g) return NULL;

    g->adj_list = malloc(vertices * sizeof(Edge*));
    g->labels = malloc(vertices * sizeof(char*));

    for (size_t i = 0; i < vertices; ++i) {
        g->labels[i] = malloc(LABEL_SIZE * sizeof(char));
        sprintf(g->labels[i], "v%d", (int)i);

        g->adj_list[i] = NULL;
    }

    g->num_vertices = vertices;
    g->num_edges = 0;

    return g;
}

void free_graph(Graph* g) {
    for (size_t i = 0; i < g->num_vertices; ++i) {
        Edge *curr = g->adj_list[i];
        while (curr) {
            Edge *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        free(g->labels[i]);
    }

    free(g->adj_list);
    free(g->labels);
    free(g);
}

static bool is_valid_vertex(Graph* g, int v)
{      return v < 0 || v >= g->num_vertices;    }


bool add_edge(Graph* g, int src, int dest) {
    if (!is_valid_vertex(g, src) || !is_valid_vertex(g, dest))
        return false;

    Edge *new_edge = malloc(sizeof(Edge));
    if(!new_edge) return false;

    // create a new adjacency
    new_edge->neighbor = dest;
    // connect the old
    new_edge->next = g->adj_list[src];
    // restart the chain with new connection
    g->adj_list[src] = new_edge;

    ++g->num_edges;

    return true;
}

bool remove_edge(Graph* g, int src, int dest) {
    if (!is_valid_vertex(g, src) || !is_valid_vertex(g, dest))
        return false;
    else if (!g->adj_list[src])
        return false;

    // edge is @ front of list
    if (g->adj_list[src]->neighbor == dest) {
        Edge *tmp = g->adj_list[src];
        g->adj_list[src] = g->adj_list[src]->next;

        free(tmp);
        --g->num_edges;
        return true;
    }

    Edge *curr = g->adj_list[src];
    while (curr->next) {
        if (curr->next->neighbor == dest) {
            Edge *tmp = curr->next;
            curr->next = curr->next->next;

            free(tmp);
            --g->num_edges;
            return true;
        }
        curr = curr->next;
    }

    return false;
}

void print_graph(Graph* g) {
    for (size_t i = 0; i < g->num_vertices; ++i) {
        printf("%s: ", g->labels[i]);
        Edge *curr = g->adj_list[i];
        while(curr) {
            printf("%s ", g->labels[curr->neighbor]);
            curr = curr->next;
        }
        printf("\n");
    }
}


int degree(Graph* g, int v) {
    if (!is_valid_vertex(g, v))
        return -1;

    int count = 0;
    Edge *curr = g->adj_list[v];
    while(curr) {
        curr = curr -> next;
        ++count;
    }

    return count;
}

int total_degree(Graph* g) {
    int count = 0;
    for (size_t i = 0; i < g->num_vertices; ++i)
        count += degree(g, i);
    return count;
}
