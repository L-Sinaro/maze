#include "partitions.h"


static int max(int x, int y)
{
    int v = x;
    if (y > x)
    {
        v = y;
    }
    return v;
}



bool estUneRacine(Partition_t partition, int i)
{
    return partition.tab[i] == i;
}


Partition_t creer(int size)
{
    Partition_t partition;
    int i;
    partition.size = size;

    partition.tab = malloc(size*sizeof(int));
    if (partition.tab)
    {
        for (i=0; i<size; i++)
        {
            partition.tab[i] = i;
        }
    }

    partition.hauteur = malloc(size*sizeof(int));
    if (partition.hauteur)
    {
        for (i=0; i<size; i++)
        {
            partition.hauteur[i] = 0;
        }
    }
    return partition;
}

void libererPartition(Partition_t partition)
{
    free(partition.tab);
    free(partition.hauteur);
}


int recupererClasse(Partition_t partition, int x)
{
    int i = x;
    while (!estUneRacine(partition,i))
    {
        i = partition.tab[i];
    }

    return i;
}

void fusionner(Partition_t partition, int x, int y)
{
    int racineX = recupererClasse(partition, x);
    int racineY = recupererClasse(partition, y);
    if (partition.hauteur[racineX] <= partition.hauteur[racineY])
    {
        partition.tab[racineX] = racineY;
        partition.hauteur[racineY] += max(partition.hauteur[racineY], partition.hauteur[racineX]+1);
    }
    else
    {
        partition.tab[racineY] = racineX;
        partition.hauteur[racineY] += max(partition.hauteur[racineX], partition.hauteur[racineY]+1);
    }
}


Maillon_t ** genererListeFils(Partition_t partition)
{
    Maillon_t ** fils = calloc(sizeof(Maillon_t*), partition.size);
    int i;

    for (i=0; i<partition.size; i++)
    {
        insererMaillonLC(&(fils[partition.tab[i]]), i);
    }

    return fils;
}


void libererTableauFils(Partition_t partition, Maillon_t ** tableauFils)
{
    int i;

    if (tableauFils)
    {
        for (i=0; i<partition.size; i++)
        {
            libererLC(tableauFils[i]);
        }
        free(tableauFils);
    }
}


Maillon_t * genererListeRacines(Partition_t partition)
{
    Maillon_t * cour = NULL;
    int i;

    for (i=0; i<partition.size; i++)
    {
        if (estUneRacine(partition, i))
        {
            insererMaillonLC(&cour, i);
        }
    }

    return cour;
}


static void parcourirFils(Maillon_t ** fils, Maillon_t * cour, Partition_t partition)
{
    if (cour != NULL)
    {
        printf("%d ", cour->v);
        parcourirFils(fils, cour->suivant, partition);
        if (!estUneRacine(partition,cour->v))
        {
            parcourirFils(fils, fils[cour->v], partition);
        }
        
    }
}

void listerClasse(Partition_t partition, int etiquette)
{
    Maillon_t ** tableauFils = genererListeFils(partition);
    int classe = recupererClasse(partition, etiquette);
    parcourirFils(tableauFils, tableauFils[classe], partition);
    printf("\n");

    libererTableauFils(partition, tableauFils);
}



void listerPartitions(Partition_t partition)
{
    Maillon_t ** tableauFils = genererListeFils(partition);
    Maillon_t * racines = genererListeRacines(partition);
    Maillon_t * cour = racines;
    
    while (cour)
    {
        printf("Classe de %d : ", cour->v);
        parcourirFils(tableauFils, tableauFils[cour->v], partition);
        printf("\n");

        cour = cour->suivant;
    }

    libererTableauFils(partition, tableauFils);
    libererLC(racines);
}