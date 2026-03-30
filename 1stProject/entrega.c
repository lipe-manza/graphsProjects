/*
Luiz Felipe Manzoli Franceschini - 16913300
Mateus Juares Felipe - 16891602
Felipe Fabiano
Juan
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct graph
{
    int **matrix;
    int vtNum;
    int edNum;
} Graph;

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
    g->edNum = 0;

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
    (*g) = NULL;

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
    // Verificação para ver se a entrada da função é válida
    if (g == NULL || v1 < 1 || v2 < 1 || v1 > g->vtNum || v2 > g->vtNum)
        return;

    // Adiciona as arestas entre dois vértices na posicao n-1 da matriz
    g->matrix[v1 - 1][v2 - 1] = w;
    g->matrix[v2 - 1][v1 - 1] = w;
    g->edNum++;
}

int exist_edge(Graph *g, int v1, int v2)
{
    // verificação padrão para ver se a entrada é valida
    if (g == NULL || v1 < 1 || v2 < 1 || v1 >= g->edNum || v2 >= g->edNum)
        return 0;

    return (g->matrix[v1 - 1][v2 - 1] != -1) ? 1 : 0;
}

int *neighbors(Graph *g, int v1)
{

    if (g == NULL)
        return NULL;

    int count = 0;
    int *temp = malloc(g->vtNum * sizeof(int *));

    for (int i = 0; i < g->vtNum; i++)
    {
        if (g->matrix[v1 - 1][i] != -1)
        {
            temp[count++] = i + 1;
        }
    }

    temp[count] = -1;
    return temp;
}

int remove_edge(Graph *g, int v1, int v2)
{
    if (g->matrix[v1][v2] == -1 || v1 > g->vtNum || v2 > g->vtNum)
    {
        return -1;
    }

    g->matrix[v1 - 1][v2 - 1] = -1;
    g->matrix[v2 - 1][v1 - 1] = -1;

    g->edNum--;
    return 1;
}

void print_info(Graph *g)
{
    if (!g)
        return;

    printf("V = [");
    for (int i = 0; i < g->vtNum; i++)
    {
        printf("%d%s", i + 1, (i == g->vtNum - 1) ? "" : ", ");
    }
    printf("]\n");

    printf("E = [");
    int count = 0;

    // Printa a diagonal de baixo da matriz no formato (coluna , linha)
    for (int j = 0; j < g->vtNum; j++)
    {
        for (int i = 0; i <= j; i++)
        {
            if (g->matrix[i][j] != -1)
            {
                count++;
                printf("(%d, %d)%s", i + 1, j + 1, (count < g->edNum) ? ", " : "");
            }
        }
    }

    printf("]\n");
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

int getVtNum(Graph *g)
{
    return g->vtNum;
}

int main(void)
{
    int option;
    int N, x, y, w;
    int res;
    bool print_status = 1;
    int *p;
    int **m;

    Graph *G;

    scanf("%d", &option);

    while (option != -1)
    {
        switch (option)
        {
        case 0:
            scanf("%d", &N);
            G = MyGraph(N);
            break;
        case 1:
            scanf("%d %d %d", &x, &y, &w);
            add_edge(G, x, y, w);
            break;
        case 2:
            scanf("%d %d", &x, &y);
            res = exist_edge(G, x, y);
            printf("%d\n", res);
            print_status = 0;
            break;
        case 3:
            scanf("%d", &x);
            p = neighbors(G, x);
            for (int i = 0; i < getVtNum(G); i++)
            {
                if (p[i] == -1)
                    break;
                else
                    printf("%d ", p[i]);
            }
            print_status = 0;
            free(p);
            break;
        case 4:
            scanf("%d %d", &x, &y);
            res = remove_edge(G, x, y);
            if (res == -1)
            {
                printf("-1");
                print_status = 0;
            }
            break;
        case 5:
            m = adjacency_matrix(G);
            printf("Adjacency Matrix:\n");
            for (int i = 0; i < getVtNum(G) - 1; i++)
            {
                printf("  "); // Da dois espaços antes de cada linha
                for (int j = 0; j < getVtNum(G) - 1; j++)
                {
                    if (m[i][j] == -1)
                        printf("0%s", (m[i][j + 1] > 9) ? "  " : "   ");
                    else
                        printf("%d%s", m[i][j], (m[i][j + 1] > 9) ? "  " : "   "); // 2 espaços se < 9 e 3 se > 9
                }
                printf("\n");
            }
            print_status = 0;
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
        scanf(" %d", &option);
    }

    if (print_status)
        print_info(G);

    remove_graph(&G);
    return 0;
}
