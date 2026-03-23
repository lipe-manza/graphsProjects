#include <stdio.h>
#include <stdbool.h>
#include "graphs.h"

int main(void)
{
    int option;
    int N, x, y, w;
    int res;
    bool print_status = 1;

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
            print_status = 0;
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
        scanf("%d", &option);
    }

    if (option == -1)
        if (print_status)
            print_info(G);
        else
            printf("%d\n", res);

    remove_graph(&G);
    return 0;
}
