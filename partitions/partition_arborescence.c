#include "partition_arborescence.h"

partition_arborescence_t * creer_pa(int taille)
{
    partition_arborescence_t * pa = NULL;
    int i;

    pa = malloc(sizeof(partition_arborescence_t));
    if (pa)    
    {
        (*pa).tab = malloc(sizeof(int)*taille);
        (*pa).hauteur = malloc(sizeof(int)*taille);
        if ((*pa).tab)
        {
            (*pa).size = taille;
            for (i=0; i<taille; ++i)
            {
                ((*pa).tab)[i] = i;
                ((*pa).hauteur)[i] = 0;
            }
        }
    }
    else
    {
        printf("allocation non reussie\n");
    }

    return pa;
}

void libere_pa(partition_arborescence_t* pa)
{
    free((*pa).tab);
    free((*pa).hauteur);
    free(pa);
}

static int recherche_classe(partition_arborescence_t* pa, int x)
{
    int i = x;

    while (((*pa).tab)[i] != i)
    {
        i = ((*pa).tab)[i];
    }

    return i;
}


void fusion_pa(partition_arborescence_t* pa, int x, int y)
{
    int racine_x = recherche_classe(pa, x);
    int racine_y = recherche_classe(pa, y);

    if (((*pa).hauteur)[racine_y] > ((*pa).hauteur)[racine_x])
    {
        ((*pa).tab)[racine_x] = racine_y;
        ((*pa).hauteur)[racine_x] = 0;
    }
    else
    {
        if (((*pa).hauteur)[racine_x] == ((*pa).hauteur)[racine_y])
        {
            (((*pa).hauteur)[racine_x])++;
        }
        ((*pa).tab)[racine_y] = racine_x;
        ((*pa).hauteur)[racine_y] = 0;
    }
}

static void affiche_arbre(cellule_t ** table, int x)
{   
    cellule_t * cour = table[x];
    //cellule_t * temp;
    int val;
    while (cour)
    {   
        val = (*cour).valeur;
        printf("%d ", val);
        //temp = cour;
        cour = (*cour).suiv;
        //free(temp);
        if ((cour) && (((*cour).valeur) != x))
        {
            affiche_arbre(table, (*cour).valeur);
        }
    }
}

static void affiche_arbre_libere(cellule_t ** table, int x)
{   
    cellule_t * cour = table[x];
    cellule_t * temp;
    int val;
    while (cour)
    {   
        val = (*cour).valeur;
        printf("%d ", val);
        temp = cour;
        cour = (*cour).suiv;
        free(temp);
        if ((cour) && (((*cour).valeur) != x))
        {
            affiche_arbre_libere(table, (*cour).valeur);
        }
    }
}

void lister_classe_pa(partition_arborescence_t * pa, int x)
{
    cellule_t ** table;
    int taille =  (*pa).size;
    cellule_t * cel;
    int i;
    
    table = calloc(taille, sizeof(cellule_t *));
    for (i=0; i<taille;++i)
    {
        cel = creation_bloc(i);
        adj_cel(cel, &(table[((*pa).tab)[i]]));
    }

    affiche_arbre(table,  (recherche_classe(pa, x)));

    for (i=0; i<taille;++i)
    {
        libere_ls(&(table[i]));
    }
    free(table);
}

cellule_t ** table_classe_pa(partition_arborescence_t * pa)
{
    cellule_t ** table;
    int taille =  (*pa).size;
    cellule_t * cel;
    int i;
    
    table = calloc(taille, sizeof(cellule_t *));
    for (i=0; i<taille;++i)
    {
        cel = creation_bloc(i);
        adj_cel(cel, &(table[((*pa).tab)[i]]));
    }

    //affiche_arbre(table,  (recherche_classe(pa, x)));

    return table;
}

void lister_partition_pa(partition_arborescence_t * pa)
{
    cellule_t ** table = NULL;
    int taille = (*pa).size;
    int i;
    cellule_t * cel;

    table = calloc(taille, sizeof(cellule_t *));
    
    for (i=0; i<taille;++i)
    {
        cel = creation_bloc(i);
        adj_cel(cel, &(table[((*pa).tab)[i]]));
    }

    for (i=0; i<taille;i++)
    {
        if ((table[i]) && (i == ((*pa).tab)[i]))
        {
            printf("classe %d :\n", i);
            affiche_arbre_libere(table, i);
            printf("\n");
        }
    }

    free(table);
}