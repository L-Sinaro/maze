#ifndef TAS_H
#define TAS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int noeud;
    int poids;
} noeud_t;


typedef struct
{
    int nb_noeuds;
    int * indexes_tas;
    noeud_t ** liste_voisins;
} graphe_djikstra_t;

typedef struct
{
    int capacity;
    int size;
    noeud_t * tab;
} tas_t;


tas_t * createtas(int capacite);

void insertNode(tas_t *tas, noeud_t noeud, int * tabIndex);

void percoleHaut(tas_t *tas, int * tabIndex, int i);

noeud_t popTas(tas_t *tas, int * tabIndex);

void printTab(int * tab, int size);

void swapNoeud(noeud_t * x, noeud_t * y);

void freetas(tas_t *tas);

//void tri_tas(int * tab, int taille);


#endif 