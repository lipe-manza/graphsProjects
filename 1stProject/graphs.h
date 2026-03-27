#ifndef GRAPHS_H
#define GRAPHS_H

#include <stdbool.h>

typedef struct graph Graph;

Graph *MyGraph(int size);

void remove_graph(Graph **g);

void add_edge(Graph *g, int v1, int v2, int w);

bool exist_edge(Graph *g, int v1, int v2);

int *neighbors(Graph *g, int v1);

bool remove_edge(Graph *g, int v1, int v2);

void print_info(Graph *g);

int max_neighbors(Graph *g);

int **adjacency_matrix(Graph *g);

#endif
