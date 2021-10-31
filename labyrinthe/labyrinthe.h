#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

#define NORD 1
#define SUD 2
#define EST 4
#define OUEST 8
#define DEPART 16
#define ARRIVEE 32

typedef struct
{
    int lignes;
    int colonnes;
    int ** tab;
} labyrinthe_t;


typedef struct
{
    int i;
    int j;
} Coordonnees_t;


void printLabyrinthe(labyrinthe_t * labyrinthe);

labyrinthe_t * initLabyrinthePLein(int lignes, int colonnes);
void conversion_graphe_coordonneees_tab(int x, int colonnes, int * i, int * j);
Coordonnees_t getCoordonneesFromGraphe(int x, labyrinthe_t labyrinthe);
void libereLabyrinthe(labyrinthe_t * labyrinthe);
int getValueFromCoordonneesIJ(int i, int j, int colonnes);
int getValueFromCoordonnees(Coordonnees_t coordonnees, labyrinthe_t labyrinthe);
labyrinthe_t * initLabyrintheAleatoire(int lignes, int colonnes, int p, graphe_t * res);
labyrinthe_t * initLabyrintheAleatoireSansCycle(int lignes, int colonnes, graphe_t * res);
Coordonnees_t gerererCoordonneesAleatoires(labyrinthe_t labyrinthe);

#endif 