#include "partition_marqueurs.h"
#include "liste_chainee.h"

partition_marqueurs_t * creer_pm(int taille)
{
    partition_marqueurs_t * pm = NULL;
    int i;

    pm = malloc(sizeof(partition_marqueurs_t));
    if (pm)    
    {
        (*pm).tab = malloc(sizeof(int)*taille);
        if ((*pm).tab)
        {
            (*pm).size = taille;
            for (i=0; i<taille; ++i)
            {
                ((*pm).tab)[i] = i;
            }
        }
    }
    else
    {
        printf("allocation non reussie\n");
    }

    return pm;
}

void libere_pm(partition_marqueurs_t * pm)
{
    free((*pm).tab);
    free(pm);
}

void printTab(int * tab, int size)
{
    int i;
    for (i=0; i<size; ++i)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void fusion_pm(partition_marqueurs_t * pm, int a, int b)
{
    int i;
    int taille = ((*pm).size);

    if ((a < taille) && (b < taille))
    {
        int classe_a = ((*pm).tab)[a];
        int classe_b = ((*pm).tab)[b];

        for (i=0; i<taille;++i)
        {
            if (((*pm).tab)[i] == classe_b)
            {
                ((*pm).tab)[i] = classe_a;
            }
        }
    }
    else
    {
        printf("valeurs non valides\n");
    }
}

void lister_classe_pm(partition_marqueurs_t * pm, int classe)
{
    int i;

    for (i=0; i<((*pm).size);++i)
    {
        if (((*pm).tab)[i] == classe)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void lister_partition_pm(partition_marqueurs_t * pm)
{
    cellule_t ** table = NULL;
    int taille = (*pm).size;
    int i;
    cellule_t * cel;

    table = calloc(taille, sizeof(cellule_t *));
    for (i=0; i<taille;++i)
    {
        cel = creation_bloc(i);
        adj_cel(cel, &(table[((*pm).tab)[i]]));
    }
    for (i=0; i<taille;++i)
    {
        if (table[i])
        {
            printf("classe %d :\n", i);
            affiche_ls(table[i]);
        }
    }
    for (i=0; i<taille;++i)
    {
        libere_ls(&(table[i]));
    }
    free(table);
}