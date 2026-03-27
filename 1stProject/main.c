#include <stdio.h>
#include "graphs.h"
#include <stdlib.h>
#include <stdbool.h>

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
