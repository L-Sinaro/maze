#ifndef SCORING_H 
#define SCORING_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_ttf.h> 

void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);
void affiche_scorechar(char * scorechar, int x, int y, SDL_Color color,TTF_Font * font, SDL_Window * window, SDL_Renderer * renderer);
void affiche_gameOver(int x, int y, SDL_Color color,TTF_Font * font, SDL_Window * window, SDL_Renderer * renderer);


#endif