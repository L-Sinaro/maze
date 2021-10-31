#include "liste_chainee.h"

/* ----------------------------------------------------------------------------- */
/* adjonction_apres   Ajoute un élément dans une liste chainée                   */
/*                                                                               */
/* En entrée: e element a inserer                                                */ 
/*            prec le pointeur du précedent de l'élément à supprimer             */
/* ----------------------------------------------------------------------------- */

void adj_cel(cellule_t * e, cellule_t ** prec)
{
  (*e).suiv = (*prec);
  *prec = e;
}

/* ----------------------------------------------------------------------------- */
/* creation_bloc creer un bloc pour une liste chainee avec la valeur v           */
/*                                                                               */
/* En entrée : c la valeur que contiendra le bloc                                */
/* En sortie : bloc l'adresse du bloc contenant v                                */
/* ----------------------------------------------------------------------------- */

cellule_t * creation_bloc(int v)
{
  cellule_t       * bloc;

  bloc = malloc(sizeof(cellule_t));

  if (bloc)
  {
    (*bloc).valeur = v;
    (*bloc).suiv = NULL;
  }
  return bloc;
}


void affiche_ls(cellule_t * t)
{
  cellule_t       * cour;                         /*   Pointeur courant                                                                  */

  cour = t;
  
  while (cour != NULL)
  {                                               /*   Affichage du numero d'usine, de la periode et du cout                             */   
    printf("%d ", (*cour).valeur);
    cour = (*cour).suiv;                          /*   On avance le pointeur courant                                                     */
  }
  printf("\n");
}

/* ----------------------------------------------------------------------------- */
/* suppression   Supprime un élément dans une liste chainée                      */
/*                                                                               */
/* En entrée : prec le pointeur du précedent de l'élément à supprimer            */
/* ----------------------------------------------------------------------------- */

void suppression(cellule_t ** prec)
{
    cellule_t     * temp;

    temp = *prec;
    *prec= (*temp).suiv;
    free(temp);
}

void libere_ls(cellule_t ** t)
{
  while ((*t) != NULL)
  {
    suppression(t);                                 /*   Suppression de chaque element en tete de la liste chainee                        */
  }
}

























