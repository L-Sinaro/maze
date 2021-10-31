#include "matrices.h"

int ** initMatriceAdjacence(int size)
{
    int i;
    int j;
    int ** tab;
    
    tab = malloc(sizeof(int *)*size);
    srand((time(NULL)));

    for (i=1; i<size; ++i)
    {
        tab[i] = calloc(i, sizeof(int));
    }

    for (i=1; i<size; ++i)
    {
        for (j=0; j<i; ++j)
        {
            if ( ((float) (rand()))/((float) RAND_MAX) > 0.8)
            {
                tab[i][j] = 1;
            }
        }
    }

    return tab;
}

void affiche_tab(int ** tab, int size)
{
    int i;
    int j;

    for (i=0; i<size; ++i)
    {
        for (j=0; j<i; ++j)
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void libere_tab(int ** tab, int size)
{
    int i;

    for (i=0; i<size; ++i)
    {
        free(tab[i]);
    }
    free(tab);
}

partition_arborescence_t * composantes_connexes(int ** tab, int size)
{
    partition_arborescence_t * pa = creer_pa(size);
    int i;
    int j;

    for (i=0; i<size; ++i)
    {
        for (j=0; j<i; ++j)
        {
            if (tab[i][j])
            {
                fusion_pa(pa, i, j);
            }
        }
    }

    return pa;
}

