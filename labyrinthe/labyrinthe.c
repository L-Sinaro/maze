#include "labyrinthe.h"

void printLabyrinthe(labyrinthe_t * labyrinthe)
{
    int i;
    int j;

    for (i=0; i<(*labyrinthe).lignes; ++i)
    {
        for (j=0; j<(*labyrinthe).colonnes; ++j)
        {
            printf("%d ", (*labyrinthe).tab[i][j]);
        }
        printf("\n");
    }
}

labyrinthe_t * initLabyrinthePLein(int lignes, int colonnes)
{
    labyrinthe_t * labyrinthe;
    int ** tab;
    int i;
    int j;

    labyrinthe = malloc(sizeof(labyrinthe_t));
    (*labyrinthe).lignes = lignes;
    (*labyrinthe).colonnes = colonnes;
    tab = malloc(sizeof(int *)*lignes); 

    if (tab)
    {
        for (i=0;i<lignes; ++i)
        {
            tab[i] = malloc(sizeof(int)*colonnes); 
            if (tab[i])
            {
                for (j=0;j<colonnes; ++j)
                {
                    tab[i][j] = NORD + SUD + EST + OUEST;
                }
            }
        }
    }

    (*labyrinthe).tab = tab;

    return labyrinthe;
}

void libereLabyrinthe(labyrinthe_t * labyrinthe)
{
    int i;

    for (i=0; i<(*labyrinthe).lignes; ++i)
    {
        free((*labyrinthe).tab[i]);
    }
    free((*labyrinthe).tab);
    free(labyrinthe);
}

void conversion_graphe_coordonneees_tab(int x, int colonnes, int * i, int * j)
{
    (*i) = x/colonnes;
    (*j) = x%colonnes;
}

Coordonnees_t getCoordonneesFromGraphe(int x, labyrinthe_t labyrinthe)
{
    Coordonnees_t coordonnees;
    coordonnees.i = x / labyrinthe.colonnes;
    coordonnees.j = x % labyrinthe.colonnes;

    return coordonnees;
}

int getValueFromCoordonneesIJ(int i, int j, int colonnes)
{
    return i*colonnes + j;
}

int getValueFromCoordonnees(Coordonnees_t coordonnees, labyrinthe_t labyrinthe)
{
    return coordonnees.i* labyrinthe.colonnes + coordonnees.j;
}

labyrinthe_t * initLabyrintheAleatoire(int lignes, int colonnes, int p, graphe_t * res)
{
    labyrinthe_t * labyrinthe;
    graphe_t * graphe;
    aretes_t * liste;

    Coordonnees_t coordonnees1;
    Coordonnees_t coordonnees2;

    labyrinthe = initLabyrinthePLein(lignes, colonnes);
    graphe = initGrapheLabyrinthe(lignes, colonnes);
    shuffleFY(graphe);
    *res = *kruskalGrapheAvecProba(graphe, p);
    liste = (*res).liste_aretes;

    
    int i;
    for (i=0;i<(*res).nb_aretes;++i)
    {
        coordonnees1 = getCoordonneesFromGraphe(liste[i].i, *labyrinthe);
        coordonnees2 = getCoordonneesFromGraphe(liste[i].j, *labyrinthe);

        if (coordonnees1.i == coordonnees2.i)
        {
            labyrinthe->tab[coordonnees1.i][coordonnees1.j] -= EST;
            labyrinthe->tab[coordonnees2.i][coordonnees2.j] -= OUEST;
        }
        else
        {
            labyrinthe->tab[coordonnees1.i][coordonnees1.j] -= SUD;
            labyrinthe->tab[coordonnees2.i][coordonnees2.j] -= NORD;
        }
    }

    libere_graphe(graphe);

    return labyrinthe;
}


labyrinthe_t * initLabyrintheAleatoireSansCycle(int lignes, int colonnes, graphe_t * res)
{
    return initLabyrintheAleatoire(lignes, colonnes, 1, res);
}



Coordonnees_t gerererCoordonneesAleatoires(labyrinthe_t labyrinthe)
{
    Coordonnees_t coordonnees;
    coordonnees.i = rand()%labyrinthe.lignes;
    coordonnees.j = rand()%labyrinthe.colonnes;
    
    return coordonnees;
}