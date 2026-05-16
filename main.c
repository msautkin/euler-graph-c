#include <stdio.h>

#include "graph.h"

void print_degrees(Graph*);

int main(int argc, char **argv) {

    printf("Test 1: simple triangle\n");
    Graph *g1 = init_graph(3);
    add_edge(g1, 0, 1);
    add_edge(g1, 1, 2);
    add_edge(g1, 2, 0);
    print_graph(g1);
    print_degrees(g1);
    printf("Connected: %s\n", is_connected(g1) ? "yes" : "no");
    printf("Eulerian: %s\n", is_eulerian(g1) ? "yes" : "no");
    hierholzer(g1, 0);
    free_graph(g1);

    printf("\nTest 2: square with diagonals\n");
    Graph *g2 = init_graph(5);
    add_edge(g2, 0, 1);
    add_edge(g2, 1, 2);
    add_edge(g2, 2, 3);
    add_edge(g2, 3, 4);
    add_edge(g2, 4, 0);
    add_edge(g2, 0, 2);
    add_edge(g2, 2, 4);
    add_edge(g2, 4, 1);
    add_edge(g2, 1, 3);
    add_edge(g2, 3, 0);
    print_graph(g2);
    print_degrees(g2);
    printf("Connected: %s\n", is_connected(g2) ? "yes" : "no");
    printf("Eulerian: %s\n", is_eulerian(g2) ? "yes" : "no");
    hierholzer(g2, 0);
    free_graph(g2);

    printf("\nTest 3: odd degree graph\n");
    Graph *g3 = init_graph(4);
    add_edge(g3, 0, 1);
    add_edge(g3, 1, 2);
    add_edge(g3, 2, 3);
    print_degrees(g3);
    printf("Connected: %s\n", is_connected(g3) ? "yes" : "no");
    printf("Eulerian: %s\n", is_eulerian(g3) ? "yes" : "no");
    hierholzer(g3, 0);
    free_graph(g3);

    printf("\nTest 4: disconnected graph\n");
    Graph *g4 = init_graph(4);
    add_edge(g4, 0, 1);
    add_edge(g4, 2, 3);
    print_graph(g4);
    print_degrees(g4);
    printf("Connected: %s\n", is_connected(g4) ? "yes" : "no");
    printf("Eulerian: %s\n", is_eulerian(g4) ? "yes" : "no");
    hierholzer(g4, 0);
    free_graph(g4);

    return 0;
}



void print_degrees(Graph* g) {
    printf("Degrees:\n");
    for (int i = 0; i < g->num_vertices; ++i)
        printf(" %s: %d\n", g->labels[i], degree(g, i));
    printf(" total: %d\n", total_degree(g));
}
