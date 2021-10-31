#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define alive = true;
#define dead = false;

void freeGrid(bool ** grid, int height);
bool ** allocateGrid(int width, int height);
void initializeGridRandomly(bool ** grid, int width, int height);
void initializeGridWithAGlider(bool ** grid);
void displayGrid(bool ** grid, int width, int height);
int numberOfNeighbours(bool ** grid, int i, int j, int width, int height);
void evolveGrid(bool ** old, bool ** new, bool survive[9], bool birth[9], int width, int height);
void swapGrid(bool *** adrGrid1, bool *** adrGrid2);
#endif