#include "parcours_profondeur.h"

void explorer(graphe_djikstra_t gd, int noeud)
{
    int k = 0;
    int noeudVoisin;
    printf("%d ", noeud);
    gd.indexes_tas[noeud] = -2;

    while ((k<4) && (((gd.liste_voisins)[noeud][k]).noeud != -1) )
    {
        noeudVoisin = ((gd.liste_voisins)[noeud][k]).noeud;
        if (gd.indexes_tas[noeudVoisin] != -2)
        {
            explorer(gd, noeudVoisin);
        }
        ++k;
    }
}

void parcours_profondeur_graphe(graphe_t graphe)
{
    int i;
    graphe_djikstra_t gd = converti_graphe(graphe);
    for (i=0;i<gd.nb_noeuds; ++i)
    {
        if (gd.indexes_tas[i] != -2)
        {
            explorer(gd, i);
        }
    }
    printf("\n");
}