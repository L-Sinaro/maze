#include <stdio.h>
#include <stdlib.h>
#include "tas.h"
#include <time.h>


int intComparator ( const void * first, const void * second ) 
{
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

int main()
{

    int tab1[14] = {2, 8, 4, 11, 9, 32, 1, 9, 54, 63, 4 , 8, 9, 20};
    int tab2[14] = {2, 8, 4, 11, 9, 32, 1, 9, 54, 63, 4 , 8, 9, 20};
    int t0;
    int t1;
    int * liste1;
    int * liste2;
    int taille = 5000000; 

    printf("avant tri : ");
    printTab(tab1, 14);
    tri_tas(tab1, 14);
    printf("résultat apres tri par tas : \n" );
    printTab(tab1, 14);
    qsort(tab2, 14, sizeof(int), intComparator);
    printf("résultat apres qsort : \n");
    printTab(tab2, 14);
    creerListeAleatoire(taille, &liste1, &liste2);
    t0 = time(NULL);
    tri_tas(liste1, taille);
    t1 = time(NULL);
    printf("temps d'exécution apres tri par tas pour %d elements : %d\n", taille, t1-t0 );
    t0 = time(NULL);
    qsort(liste2, taille, sizeof(int), intComparator);
    t1 = time(NULL);
    printf("temps d'exécution apres qsort pour %d elements : %d\n", taille, t1-t0 );
    free(liste1);
    free(liste2);
    return 0;
}
