#ifndef MATRICES_H
#define MATRICES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partition_arborescence.h"

#define TAILLE 10

int ** initMatriceAdjacence(int size);
void affiche_tab(int ** tab, int size);
void libere_tab(int ** tab, int size);
partition_arborescence_t * composantes_connexes(int ** tab, int size);

#endif 