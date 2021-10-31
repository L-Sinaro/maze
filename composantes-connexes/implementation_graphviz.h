#ifndef IMPLEMENTATION_GRAPHVIZ_H
#define IMPLEMENTATION_GRAPHVIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include "matrices.h"
#include "liste_chainee.h"
#include "partition_arborescence.h"
#include "graphe.h"

void matrice_graph(int ** tab, int size);
void lister_graph_composantes_connexes(partition_arborescence_t * pa);
void creer_graph(partition_arborescence_t * pa, cellule_t ** table, int i);
void graphe_graph(graphe_t * graphe);
void lister_foret(partition_arborescence_t * pa);
void graphe_arbre(graphe_t * graphe);
#endif 