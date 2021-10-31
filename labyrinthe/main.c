#include <stdio.h>
#include "partition_arborescence.h"
#include "graphe.h"
#include "kruskal.h"
#include "labyrinthe.h"
#include "sdl.h"
#include "djikstra.h"
#include "Aetoile.h"


int main()
{
    srand(time(NULL));

    labyrinthe_t * labyrinthe;
    graphe_t graphe;
    // graphe_djikstra_t graphe_djikstra;
    //int * tabRes;
    int lignes = 5;
    int colonnes = 10;
    cellule_t * res;

    //labyrinthe = initLabyrinthePLein(5, 5);
    labyrinthe = initLabyrintheAleatoire(lignes, colonnes, 0.7, &graphe);
    printLabyrinthe(labyrinthe);
    //tabRes = djikstra(4, graphe);
    res = plus_court_chemin_djikstra(1, 20, graphe);
    printf("liste aretes\n");
    affiche_liste_aretes(&graphe);
    printf("chemin Djikstra : \n");
    affiche_ls(res);
    libere_ls(&res);
    //printTab(tabRes, graphe.nb_noeuds);
    //printf("essai : %d\n", distance_euclidienne(0, 19, colonnes));
    res = plus_court_chemin_aetoile(1, 20, graphe, colonnes);
    printf("chemin Aetoile : \n");
    affiche_ls(res);
    libere_ls(&res);
    // playGame();
    parcoursPlusCoursCheminAutomatique();
    
    libereLabyrinthe(labyrinthe);

    return 0;
}