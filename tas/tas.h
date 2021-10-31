#ifndef TAS_H
#define TAS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int capacity;
    int size;
    int *tab;
} tas_t;

tas_t* createtas(int capacite);

void insertNode(tas_t *tas, int value);

int popTas(tas_t *tas);

void printTab(int * tab, int size);

void swapInt(int * x, int * y);

void freetas(tas_t *tas);

void tri_tas(int * tab, int taille);

void creerListeAleatoire(int taille, int ** liste1, int ** liste2);


#endif 