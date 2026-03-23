#include "graphs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct graph
{
    int **matrix;
    int vtNum;
};

int **createMatrix(int size);

void deleteMatrix(int ***m, int size);

Graph *MyGraph(int size)
{
    if (size < 0)
        return NULL;

    Graph *g = malloc(1 * sizeof(Graph));

    if (g == NULL)
        return g;

    g->matrix = createMatrix(size);
    g->vtNum = size;

    return g;
}

int **createMatrix(int size)
{
    int **m = malloc(size * sizeof(int *));

    if (m == NULL)
        return m;

    for (int i = 0; i < size; i++)
    {
        m[i] = malloc(size * sizeof(int));

        if (m[i] == NULL)
        {
            deleteMatrix(&m, size);
            return NULL;
        }
        for (int j = 0; j < size; j++)
        {
            m[i][j] = -1;
        }
    }

    return m;
}

void remove_graph(Graph **g)
{
    if (g == NULL || *g == NULL)
        return;

    deleteMatrix(&((*g)->matrix), (*g)->vtNum);

    free(*g);
    (*g)= NULL;

    return;
}

void deleteMatrix(int ***m, int size)
{
    if (m == NULL || *m == NULL)
        return;

    for (int i = 0; i < size; i++)
    {
        free((*m)[i]);
        (*m)[i] = NULL;
    }
    
    free(*m);
    *m = NULL;
}

void add_edge(Graph *g, int v1, int v2, int w)
{
    if (g == NULL)
        return;

    g->matrix[v1][v2] = w;
    g->matrix[v2][v1] = w;
}

bool exist_edge(Graph *g, int v1, int v2)
{
    return (g->matrix[v1][v2] != -1) ? true : false;
}

int *neighbors(Graph *g, int v1)
{

    if (g == NULL)
        return NULL;

    int count = 0;
    int temp[g->vtNum];

    printf("[");
    for (int i = 0; i < g->vtNum; i++)
    {
        if (g->matrix[v1][i] != -1)
        {
            temp[count++] = i;
            printf("%d\n", i);
        }
    }
    printf("]");

    temp[count] = -1;

    int *array = (int *)malloc(count * sizeof(int));

    int j = 0;
    while (temp[j] == -1)
    {
        array[j] = temp[j];
        j++;
    }
    return array;
}

int remove_edge(Graph *g, int v1, int v2)
{
    if (g->matrix[v1][v2] == -1)
    {
        printf("-1");
        return -1;
    }

    g->matrix[v1][v2] = -1;
    g->matrix[v2][v1] = -1;

    return g->matrix[v2][v1];
}

void print_info(Graph *g)
{
    if (g == NULL)
        return;

    printf("V = [");
    for (int i = 0; i < g->vtNum; i++)
    {
        printf("%d%s", i, (i == g->vtNum - 1) ? "" : ", ");
    }
    printf("]\n");

    printf("E = [");
    for (int i = 0; i < g->vtNum; i++)
    {
        for (int j = i; j < g->vtNum; j++)
        {
            if (g->matrix[i][j] != -1)
            {
                printf("(%d, %d)%s", i, j, (i !=j-1) ? "" : ", ");
            }
        }
    }
    printf("]");
}

int max_neighbors(Graph *g)
{
    if (g == NULL)
        return -1;

    int neighNum;
    int Cmax = 0;
    int max = 0;

    for (int i = 0; i < g->vtNum; i++)
    {
        Cmax = 0;
        for (int j = 0; j < g->vtNum; j++)
        {

            if (g->matrix[i][j] != -1)
            {
                neighNum++;
            }
        }
        Cmax = neighNum;
        if (Cmax > max)
            max = i;
    }

    return max;
}
int **adjacency_matrix(Graph *g)
{
    if (g == NULL)
        return NULL;
    return g->matrix;
}
