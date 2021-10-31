#ifndef JEU_VIE_H
#define JEU_VIE_H

#include <stdio.h>
#include <stdlib.h>

int ** initialisationGrille(int lignes, int colonnes);
void libereGrille(int ** tab, int lignes);
void initialisationExemple(int ** tab);
void affiche(int ** tab, int lignes, int colonnes) ;
int nbVoisins(int ** tab, int i, int j, int lignes, int colonnes);
void transition(int ** oldtab, int ** newtab, int lignes, int colonnes);
void echangeTab(int *** tab1, int *** tab2);

#endif