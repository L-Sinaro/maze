/***********************************************************/
/* Simon Mazenoux - Axel Pronnier                     2021 */
/*---------------------------------------------------------*/
/*                      listeChainee.h                     */
/*                                                         */
/*             Gestion d'une liste chainée                 */
/***********************************************************/


#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_BUFFER 1024


/*---------------------------------------------------------*/
/*                  STRUCTURE DE DONNEES                   */
/*---------------------------------------------------------*/

typedef struct Maillon
{
    int v;
    struct Maillon * suivant;
} Maillon_t;

/*---------------------------------------------------------*/
/*                         FONCTIONS                       */
/*---------------------------------------------------------*/

void         afficherLC(Maillon_t * liste);
Maillon_t *  insererMaillonLC(Maillon_t **pprec, int donnees);
void         supprimerMaillonLC(Maillon_t ** pprec);
void         libererLC(Maillon_t * tete);

#endif