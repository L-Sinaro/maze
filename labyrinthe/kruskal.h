#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graphe.h"
#include "partition_arborescence.h"

void affiche_aretes(aretes_t * listeAretes, int len);
graphe_t * kruskalGraphe(graphe_t * graphe);
graphe_t * kruskalGrapheAvecProba(graphe_t * graphe, float p);

#endif 