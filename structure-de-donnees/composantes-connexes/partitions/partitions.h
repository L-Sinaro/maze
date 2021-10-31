#ifndef PARTITION_H
#define PARTITION_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "liste-chainee.h"

typedef struct Partition
{
    int * tab;
    int * hauteur;
    int size;
} Partition_t;

bool         estUneRacine(Partition_t partition, int i);
Partition_t  creer(int size);
void         libererPartition(Partition_t partition);
int          recupererClasse(Partition_t partition, int x);
void         fusionner(Partition_t partition, int x, int y);
Maillon_t ** genererListeFils(Partition_t partition);
void         libererTableauFils(Partition_t partition, Maillon_t ** tableauFils);
Maillon_t *  genererListeRacines(Partition_t partition);
void         listerClasse(Partition_t partition, int etiquette);
void         listerPartitions(Partition_t partition);

#endif