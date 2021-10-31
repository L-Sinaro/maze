#ifndef PARCOURS_PROFONDEUR_H
#define PARCOURS_PROFONDEUR_H

#include <stdio.h>
#include <stdlib.h>
#include "djikstra.h"

void explorer(graphe_djikstra_t gd, int noeud);

void parcours_profondeur_graphe(graphe_t graphe);

#endif