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

void free_graph(Graph *g) {
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

static bool is_valid_vertex(Graph *g, int v)
{      return v >= 0 && v < g->num_vertices;    }


bool add_edge(Graph *g, int src, int dest) {
    if (!g) return false;
    if (!is_valid_vertex(g, src) || !is_valid_vertex(g, dest))
        return false;

    // src->dest addition
    Edge *new_edge = malloc(sizeof(Edge));
    if(!new_edge) return false;
    // create a new adjacency
    new_edge->neighbor = dest;
    // connect the old
    new_edge->next = g->adj_list[src];
    // restart the chain with new connection
    g->adj_list[src] = new_edge;

    // dest->src addition
    Edge *reverse = malloc(sizeof(Edge));
    if(!reverse) return false;
    reverse->neighbor = src;
    reverse->next = g->adj_list[dest];
    g->adj_list[dest] = reverse;

    ++g->num_edges;
    return true;
}

bool remove_edge(Graph *g, int src, int dest) {
    if (!g) return false;
    if (!is_valid_vertex(g, src) || !is_valid_vertex(g, dest))
        return false;
    if (!g->adj_list[src])
        return false;

    // src->dest removal
    if (g->adj_list[src]->neighbor == dest) {
        Edge *tmp = g->adj_list[src];
        g->adj_list[src] = g->adj_list[src]->next;

        free(tmp);
    } else {
        Edge *curr = g->adj_list[src];
        while (curr->next) {
            if (curr->next->neighbor == dest) {
                Edge *tmp = curr->next;
                curr->next = curr->next->next;

                free(tmp);
                break;
            }
            curr = curr->next;
        }
    }

    // dest->src removal
    if (g->adj_list[dest] && g->adj_list[dest]->neighbor == src) {
        Edge *tmp = g->adj_list[dest];
        g->adj_list[dest] = g->adj_list[dest]->next;
        free(tmp);
    } else {
        Edge *curr = g->adj_list[dest];
        while (curr && curr->next) {
            if (curr->next->neighbor == src) {
                Edge *tmp = curr->next;
                curr->next = curr->next->next;
                free(tmp);
                break;
            }
            curr = curr->next;
        }
    }

    --g->num_edges;
    return true;
}

void print_graph(Graph *g) {
    if (!g) return;

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


int degree(Graph *g, int v) {
    if (!g) return -1;
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

int total_degree(Graph *g) {
    if (!g) return -1;

    int count = 0;
    for (size_t i = 0; i < g->num_vertices; ++i)
        count += degree(g, i);
    return count;
}


static void dfs(Graph *g, int v, bool* visited) {
    visited[v] = true;
    Edge* curr = g->adj_list[v];
    while(curr) {
        if(!visited[curr->neighbor])
            dfs(g, curr->neighbor, visited);
        curr = curr->next;
    }
}

bool is_connected(Graph *g) {
    if (!g) return -1;

    bool *visited = calloc(g->num_vertices, sizeof(bool));
    if (!visited) return false;

    int start = -1;
    for (size_t i = 0; i < g->num_vertices; i++) {
        if (g->adj_list[i]) {
            start = i;
            break;
        }
    }

    // disjoint graph
    if (start == -1) {
        free(visited);
        return false;
    }

    dfs(g, start, visited);

    for (int i = 0; i < g->num_vertices; i++) {
        // non-isolated vertex is disjoint
        if (g->adj_list[i] && !visited[i]) {
            free(visited);
            return false;
        }
    }


    free(visited);
    return true;
}

bool is_eulerian(Graph *g) {
    if (!g) return -1;
    if (!is_connected(g))
        return false;

    for (size_t i = 0; i < g->num_vertices; i++)
        if (degree(g, i) % 2 != 0)
            return false;

    return true;
}


void hierholzer(Graph *g, int src) {
    if(!is_eulerian(g)) {
        printf("Graph is not Eulerian\n");
        return;
    }

    int *stack = malloc((g->num_edges + 1) * sizeof(int));
    int stack_top = 0;

    int *circuit = malloc((g->num_edges + 1) * sizeof(int));
    int circuit_size = 0;

    stack[stack_top++] = src;

    while(stack_top > 0) {
        int v = stack[stack_top - 1];

        if (g->adj_list[v]) {
            int next = g->adj_list[v]->neighbor;
            stack[stack_top++] = next;
            remove_edge(g, v, next);
        } else {
            circuit[circuit_size++] = v;
            --stack_top;
        }
    }

    printf("Circuit: ");
    for (int i = circuit_size - 1; i >= 0; --i)
        printf("%s ", g->labels[circuit[i]]);
    printf("\n");

    free(stack);
    free(circuit);
}
