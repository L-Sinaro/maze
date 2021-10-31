#ifndef PARTITION_ARBORESCENCE_H
#define PARTITION_ARBORESCENCE_H

#include <stdio.h>
#include <stdlib.h>
#include "liste_chainee.h"

typedef struct
{
    int size;
    int * tab;
    int * hauteur;
} partition_arborescence_t;

partition_arborescence_t * creer_pa(int taille);
void libere_pa(partition_arborescence_t* pa);
void fusion_pa(partition_arborescence_t* pa, int x, int y);
void lister_classe_pa(partition_arborescence_t * pa, int x);
void lister_partition_pa(partition_arborescence_t * pa);
cellule_t ** table_classe_pa(partition_arborescence_t * pa);

#endif 