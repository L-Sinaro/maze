#ifndef AETOILE_H
#define AETOILE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "djikstra.h"
#include "labyrinthe.h"


int distance_euclidienne(int a, int b, int colonnes);
int * Aetoile(int depart, int arrivee,  graphe_t graphe, int colonnes);
cellule_t * plus_court_chemin_aetoile(int depart, int arrivee, graphe_t graphe, int colonnes);

#endif 