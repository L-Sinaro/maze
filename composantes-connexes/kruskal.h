#include "graphe.h"
#include "partition_arborescence.h"

void affiche_aretes(aretes_t * listeAretes, int len);
graphe_t * kruskalGraphe(graphe_t * graphe, float p);
partition_arborescence_t * kruskalPartition(graphe_t * graphe);