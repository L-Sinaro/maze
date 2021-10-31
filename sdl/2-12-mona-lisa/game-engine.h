
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct Objet
{
    SDL_Texture * texture;
    float * probabilitesDePresence;
    int zoom;
} Objet_t;

enum type
{
    VIDE,
    ENNEMI,
    BONUS,
    TAILLE
};



Objet_t * initiateObjects(int height);
void freeObjects(Objet_t * objects);
void freeGrid(enum type ** grid, int height);
void resetGrid(enum type ** grid, int width, int height);
enum type ** allocateGrid(int width, int height);
void displayGrid(enum type ** grid, int width, int height, int iterateurRotor);
void ramdomizeNewColumn(enum type ** grid, int width, int height ,int iterateurRotor, Objet_t * objects);