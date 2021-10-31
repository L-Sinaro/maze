#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 
#include <math.h>
#include <stdio.h>
#include "partition_arborescence.h"
#include "graphe.h"
#include "kruskal.h"
#include "labyrinthe.h"
#include "djikstra.h"




typedef struct Offset
{
    int i;
    int j;
} Offset_t;


void playGame();
static void drawTiles(SDL_Renderer * renderer, SDL_Window* window, labyrinthe_t labyrinthe);
void parcours_plus_court_chemin_labyrinthe(labyrinthe_t labyrinthe, graphe_t graphe, SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * carTexture, SDL_Rect * car, Coordonnees_t depart, Coordonnees_t arrivee);
void parcoursPlusCoursCheminAutomatique();

#endif