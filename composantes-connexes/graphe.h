#ifndef GRAPHES_H
#define GRAPHES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partition_arborescence.h"

typedef struct
{
    int i;
    int j;
} aretes_t;

typedef struct
{
    int nb_noeuds;
    int nb_aretes;
    int capacite;
    aretes_t * liste_aretes;
} graphe_t;

void insere_arete(graphe_t * graphe, int i, int j);

graphe_t * initGraphe(int nb_noeuds);

void libere_graphe(graphe_t * graphe);

void affiche_liste_aretes(graphe_t * graphe);

partition_arborescence_t * creerPartitionGraphe(graphe_t * graphe);

graphe_t * initGrapheLabyrinthe(int n, int p);

void shuffleFY(graphe_t * graphe);

#endif 