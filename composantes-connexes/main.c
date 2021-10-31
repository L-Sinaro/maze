#include <stdio.h>
#include "partition_arborescence.h"
#include "matrices.h"
#include "implementation_graphviz.h"
#include "graphe.h"
#include "kruskal.h"

int main()
{
    //partition_arborescence_t * pa;
    
    /*
    int ** tab;
    tab = initMatriceAdjacence(TAILLE);
    affiche_tab(tab, TAILLE);
    pa = composantes_connexes(tab, TAILLE);
    lister_graph_composantes_connexes(pa);
    matrice_graph(tab, TAILLE);
    libere_tab(tab, TAILLE);
    libere_pa(pa);
    */

   /*
    graphe_t * graphe = initGraphe(TAILLE);
    printf("liste des aretes : \n");
    affiche_liste_aretes(graphe);
    graphe_graph(graphe);
    pa = creerPartitionGraphe(graphe);
    lister_graph_composantes_connexes(pa);
    libere_graphe(graphe);
    libere_pa(pa);
    */

    /*
    graphe_t * graphe = initGraphe(TAILLE);
    printf("liste des aretes : \n");
    affiche_liste_aretes(graphe);
    graphe_graph(graphe);
    pa = kruskalPartition(graphe);
    lister_foret(pa);
    libere_graphe(graphe);
    libere_pa(pa);
    */

    graphe_t * graphe = initGraphe(TAILLE);
    graphe_t * res;
    graphe = initGrapheLabyrinthe(5, 5);
    //pa = creerPartitionGraphe(graphe);
    shuffleFY(graphe);
    printf("liste des aretes : \n");
    affiche_liste_aretes(graphe);
    res = kruskalGraphe(graphe, 0.5);
    graphe_graph(graphe);
    libere_graphe(graphe);
    graphe_arbre(res);
    libere_graphe(res);
    //lister_foret(pa); //pour kruskal
    

    return 0;
}