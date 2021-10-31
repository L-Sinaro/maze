#include "tas.h"

tas_t* createtas(int capacite)
{
    tas_t * tas;
    tas = malloc(sizeof(tas));
    if (tas)
    {
        (*tas).tab = malloc(capacite*sizeof(int));   /* Prévoir l'échec de malloc */
        (*tas).capacity = capacite;
        (*tas).size = 0;
    }
    return tas;
}

void tasRealloc(tas_t *tas)
{
    int new_size = 2*(*tas).capacity;
    (*tas).tab = realloc((*tas).tab, new_size*sizeof(int));
                                         /* Prévoir l'échec de realloc */
    (*tas).capacity = new_size;
}

void swapInt(int * x, int * y)
{
    int temp;
    temp = (*x);
    (*x) = (*y);
    (*y) = temp;
}


void insertNode(tas_t *tas, int value)
{
    if((*tas).size >= (*tas).capacity) 
    {
        tasRealloc(tas);
    }
    (*tas).tab[(*tas).size] = value;
    int fils = (*tas).size;
    int parent = ((fils+1)/2)-1;
    //printf("debut insertion\n");
    while(((*tas).tab[parent] > (*tas).tab[fils]) && (fils >0) ) 
    {   //tant qu'on n'est pas à la bonne place, on fait percoler le nouveau noeud vers le haut
        swapInt(&((*tas).tab[parent]), &((*tas).tab[fils]));

        fils = parent;
        parent = ((fils+1)/2)-1;
    }

    (*tas).size++;
}

void printTab(int * tab, int size)
{
    int i;
    for (i=0; i<size; ++i)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}


int popTas(tas_t *tas)
{
    int res = -1;

    if ((*tas).size > 0)
    {
        (*tas).size--;
        res = (*tas).tab[0];
        (*tas).tab[0] = (*tas).tab[(*tas).size]; //la derniere feuille devient la racine
        int i = 0;
        int fg = 1;
        int fd = 2;
        while ((fg < (*tas).size) && (((*tas).tab[i] > (*tas).tab[fd]) || ((*tas).tab[i] > (*tas).tab[fg])) )
        {   //tant qu'on n'est pas à la bonne place, on fait percoler la nouvelle racine vers le bas
            if ((*tas).tab[fg] > (*tas).tab[fd])
            {
                swapInt(&((*tas).tab[fd]), &((*tas).tab[i]));
                i = fd;
                fg = 2*(i+1)-1;
                fd = 2*(i+1);
            }
            else 
            {
                swapInt(&((*tas).tab[fg]), &((*tas).tab[i]));
                i = fg;
                fg = 2*(i+1)-1;
                fd = 2*(i+1);
            }
        }
    }

    return res;
}


void freetas(tas_t *tas)
{
    free((*tas).tab);
    free(tas);
}

void tri_tas(int * tab, int taille)
{
    int i;
    tas_t * tas;
    tas = createtas(taille);
    for (i=0;i<taille;++i) //on fait rentrer la liste à trier dans le tas
    {
        insertNode(tas, tab[i]);
    }
    for (i=0;i<taille;++i)
    {
        tab[i] = popTas(tas); //on remet dans la liste à l'aide du pop qui conserve la structure de tas
    }

    freetas(tas);
}

void creerListeAleatoire(int taille, int ** liste1, int ** liste2)
{
    int i;
    int v;
    int * l1 = malloc(sizeof(int)*taille);
    int * l2 = malloc(sizeof(int)*taille);

    for (i=0;i<taille;++i)
    {
        v = rand();
        l1[i] = v;
        l2[i] = v;
    }

    *liste1 = l1;
    *liste2 = l2;
}