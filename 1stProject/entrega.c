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

bool exist_edge(Graph *g, int v1, int v2)
{
    // verificação padrão para ver se a entrada é valida
    if (g == NULL || v1 < 1 || v2 < 1 || v1 >= g->edNum || v2 >= g->edNum)
        return false;

    return (g->matrix[v1 - 1][v2 - 1] != -1) ? true : false;
}

int *neighbors(Graph *g, int v1)
{

    if (g == NULL)
        return NULL;

    int count = 0;
    int temp[g->vtNum];

    for (int i = 0; i < g->vtNum; i++)
    {
        if (g->matrix[v1 - 1][i] != -1)
        {
            temp[count++] = i;
            printf("%d ", i + 1);
        }
    }

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

bool remove_edge(Graph *g, int v1, int v2)
{
    if (g->matrix[v1][v2] == -1 || v1 > g->vtNum || v2 > g->vtNum)
    {
        printf("-1");
        return false;
    }

    g->matrix[v1 - 1][v2 - 1] = -1;
    g->matrix[v2 - 1][v1 - 1] = -1;

    g->edNum--;
    return true;
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

int main(void)
{
    int option;
    int N, x, y, w;
    int res;
    bool print_status = 1;
    int *p;

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
            // adicionamos
            scanf("%d %d %d", &x, &y, &w);
            add_edge(G, x, y, w);
            break;
        case 2:
            // get
            scanf("%d %d", &x, &y);
            res = exist_edge(G, x, y);
            printf("%d\n", res);
            print_status = 0;
            break;
        case 3:
            scanf("%d", &x);
            p = neighbors(G, x);
            print_status = 0;
            free(p);
            break;
        case 4:
            scanf("%d %d", &x, &y);
            if (!remove_edge(G, x, y))
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
