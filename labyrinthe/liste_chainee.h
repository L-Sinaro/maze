/*----------------------------------------------------------------*/
/*                       liste_chainee.h                          */
/*               Traitement d'une liste chainée                   */
/*----------------------------------------------------------------*/

#ifndef LISTE_H 
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>

/*--------------*/
/*   typedef    */
/*--------------*/

typedef struct cellule 
{
  int                  valeur;
  struct cellule *      suiv;
} cellule_t;


/*----------------------------------------------------*/
/*   adjonction d'un élément dans une liste chainee   */
/*----------------------------------------------------*/

void adj_cel(cellule_t * e, cellule_t ** prec);

/*------------------------*/
/*   création d'un bloc   */
/*------------------------*/

cellule_t * creation_bloc(int v);

void affiche_ls(cellule_t * t);

void suppression(cellule_t ** prec);

void libere_ls(cellule_t ** t);

#endif