#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

enum direction 
{ 
    UP, 
    DOWN, 
    LEFT, 
    RIGHT
};

typedef struct ColoredRectangle
{
    SDL_Rect rectangle;
    SDL_Color color;
} ColoredRectangle_t;

typedef struct Snake
{
    int size;
    ColoredRectangle_t * parts;
    enum direction d;
} Snake_t;

#endif