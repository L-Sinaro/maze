#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"
#include "tas.h"

graphe_djikstra_t converti_graphe(graphe_t graphe);

int * djikstra(int depart, graphe_t graphe);

cellule_t * plus_court_chemin_djikstra(int depart, int arrivee, graphe_t graphe);

#endif 