#ifndef PARTITION_MARQUEURS_H
#define PARTITION_MARQUEURS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int size;
    int * tab;
} partition_marqueurs_t;

partition_marqueurs_t * creer_pm(int taille);

void libere_pm(partition_marqueurs_t * pm);

void printTab(int * tab, int size);

void fusion_pm(partition_marqueurs_t * pm, int a, int b);

void lister_classe_pm(partition_marqueurs_t * pm, int classe);

void lister_partition_pm(partition_marqueurs_t * pm);

#endif 