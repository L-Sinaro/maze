#include "liste-chainee.h"


/*-------------------------------------------------------------------*/
/*                          afficherLC                               */
/*                                                                   */
/* Description :    Permet l'affichage du contenu d'une liste chainée*/
/*                  sur stdout de manière claire                     */
/* Entrée :         L'adresse du premier maillon                     */
/* Sortie :         Le contenu de la liste sur la sortie standard    */
/*-------------------------------------------------------------------*/

void afficherLC(Maillon_t * tete)
{
    Maillon_t * cour = tete;

    printf("Liste chainée :\n");
    while (cour)
    {   
        printf("%p : \n   - %d : ", (void *) cour, cour->v);
        printf("\n   - suivant : %p\n", (void *) cour->suivant);
        cour = cour->suivant;
    }
    printf("\n");     
}


/*-------------------------------------------------------------------*/
/*                       insererMaillonMilieuLC                      */
/*                                                                   */
/* Description :    Insére un maillon dans une liste chainée         */
/* Entrée :         Un pointeur sur le maillon précédent, ainsi que  */
/*                  les données du nouveau maillon                   */
/* Sortie :         Le nouveau maillon correctement inséré           */
/* Pré-condition :  prec != NULL                                     */
/* Post-condition : Vérifier que le maillon retourné est bien alloué */
/*-------------------------------------------------------------------*/

Maillon_t * insererMaillonLC(Maillon_t ** pprec, int v)
{
    Maillon_t * nouv = malloc(sizeof(Maillon_t));

    if (nouv)
    {
        nouv->v = v;
        nouv->suivant = *pprec;
        *pprec = nouv;
    }

    return nouv;
}



/*-------------------------------------------------------------------*/
/*                       supprimerMaillonLC                          */
/*                                                                   */
/* Description :    Supprimer un maillon différent de celui de tête  */
/* Entrée :         Un double pointeur sur le maillon précédent      */
/* Sortie :         /                                                */
/* Pré-condition :  /                                                */
/* Post-condition : /                                                */
/*-------------------------------------------------------------------*/

void supprimerMaillonLC(Maillon_t ** pprec)
{
    Maillon_t * cour;
    cour = *pprec;
    *pprec = cour->suivant;
    free(cour);
}



/*-------------------------------------------------------------------*/
/*                             libérerLC                             */
/*                                                                   */
/* Description :    Livère l'intégralité des maillons d'une liste    */
/* Entrée :         Un pointeur sur le maillon de tête               */
/* Sortie :         /                                                */
/* Pré-condition :  /                                                */
/* Post-condition : /                                                */
/*-------------------------------------------------------------------*/


void libererLC(Maillon_t * tete)
{
    // Tant que le maillon de tête ne pointe pas vers NULL
    while (tete)
    {
        // On supprime le maillon de tête
        supprimerMaillonLC(&tete);
    }
}



