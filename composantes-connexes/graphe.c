#include "graphe.h"

void insere_arete(graphe_t * graphe, int i, int j)
{
    int nb_aretes = (*graphe).nb_aretes;

    if (nb_aretes == (*graphe).capacite)
    {
        int nouvelle_cap = (*graphe).capacite*2;
        (*graphe).liste_aretes = realloc((*graphe).liste_aretes, sizeof(aretes_t)*nouvelle_cap);
        if ((*graphe).liste_aretes)
        {
            (*graphe).capacite = nouvelle_cap;
        }
    }
    (((*graphe).liste_aretes)[nb_aretes]).i = i;
    (((*graphe).liste_aretes)[nb_aretes]).j = j;
    (*graphe).nb_aretes = nb_aretes + 1;
}

graphe_t * initGraphe(int nb_noeuds)
{
    graphe_t * graphe;
    int i;
    int j;

    srand((time(NULL)));
    graphe = malloc(sizeof(graphe));
    (*graphe).nb_noeuds = nb_noeuds;
    (*graphe).liste_aretes = malloc(sizeof(aretes_t)*(nb_noeuds*2));
    (*graphe).nb_aretes = 0;
    (*graphe).capacite = nb_noeuds*2;
    for (i=0;i<nb_noeuds;++i)
    {
        for (j=i+1; j<nb_noeuds; ++j)
        {
            if ( ((float) (rand()))/((float) RAND_MAX) > 0.8)
            {
                insere_arete(graphe, i, j);
            }
        }
    }

    return graphe;
}

void libere_graphe(graphe_t * graphe)
{
    free((*graphe).liste_aretes);
    free(graphe);
}

void affiche_liste_aretes(graphe_t * graphe)
{
    int i;
    aretes_t * liste = (*graphe).liste_aretes;

    for (i=0; i<(*graphe).nb_aretes; ++i)
    {
        printf("(%d ,%d) ",  (liste[i]).i , (liste[i]).j);
    }
    printf("\n");
}

partition_arborescence_t * creerPartitionGraphe(graphe_t * graphe)
{
    int i;
    aretes_t * liste = (*graphe).liste_aretes;
    partition_arborescence_t * pa;
    pa = creer_pa((*graphe).nb_noeuds);

    for (i=0; i<(*graphe).nb_aretes; ++i)
    {
        fusion_pa(pa, (liste[i]).i, (liste[i]).j);
    }

    return pa;
}



graphe_t * initGrapheLabyrinthe(int n, int p) // n : nb de lignes et p : nb de colonnes
{
    graphe_t * graphe;
    int i;
    int j;

    graphe = malloc(sizeof(graphe));
    (*graphe).nb_noeuds = n*p;
    (*graphe).liste_aretes = malloc(sizeof(aretes_t)*(n*p));
    (*graphe).nb_aretes = 0;
    (*graphe).capacite = n*p;

    for (i=0; i<n; ++i)
    {
        for (j=0; j<p; ++j)
        {
            if (i<(n-1))
            {
                insere_arete(graphe, (i*p)+j, ((i+1)*p)+j);
            }
            if (j<(p-1))
            {
                insere_arete(graphe, (i*p)+j, (i*p)+j+1);
            }
        }
    }

    return graphe;
}

static void swapAretes(aretes_t * x, aretes_t * y)
{
    aretes_t temp;
    temp = *x;
    (*x) = (*y);
    (*y) = temp;
}

void shuffleFY(graphe_t * graphe)
{
    int i;
    int j;
    aretes_t * liste = (*graphe).liste_aretes;

    srand((time(NULL)));
    for (i=0; i<(*graphe).nb_aretes; ++i)
    {
        j = (rand())%(i+1);
        swapAretes(&(liste[i]), &(liste[j]));
    }
}
