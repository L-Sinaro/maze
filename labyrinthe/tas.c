#include "tas.h"

tas_t* createtas(int capacite)
{
    tas_t * tas;
    tas = malloc(sizeof(tas));
    if (tas)
    {
        (*tas).tab = malloc(capacite*sizeof(noeud_t));   /* Prévoir l'échec de malloc */
        (*tas).capacity = capacite;
        (*tas).size = 0;
    }
    return tas;
}

void tasRealloc(tas_t *tas)
{
    int new_size = 2*(*tas).capacity;
    (*tas).tab = realloc((*tas).tab, new_size*sizeof(noeud_t));
                                         /* Prévoir l'échec de realloc */
    (*tas).capacity = new_size;
}

void swapNoeud(noeud_t * x, noeud_t * y)
{
    noeud_t temp;
    temp = (*x);
    (*x) = (*y);
    (*y) = temp;
}


void insertNode(tas_t *tas, noeud_t noeud, int * tabIndex)
{
    if((*tas).size >= (*tas).capacity) 
    {
        tasRealloc(tas);
    }
    (*tas).tab[(*tas).size] = noeud;
    int fils = (*tas).size;
    int parent = ((fils+1)/2)-1;
    tabIndex[noeud.noeud] = fils;
    //printf("debut insertion\n");
    while ((((*tas).tab[parent]).poids > ((*tas).tab[fils]).poids) && (fils >0) ) 
    {   //tant qu'on n'est pas à la bonne place, on fait percoler le nouveau noeud vers le haut
        tabIndex[(*tas).tab[parent].noeud] = fils; 
        tabIndex[(*tas).tab[fils].noeud] = parent; 
        swapNoeud(&((*tas).tab[parent]), &((*tas).tab[fils]));
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

void percoleHaut(tas_t *tas, int * tabIndex, int i)
{
    int fils = i;
    int parent = ((fils+1)/2)-1;
    //printf("debut insertion\n");
    while ((((*tas).tab[parent]).poids > ((*tas).tab[fils]).poids) && (fils >0) ) 
    {   //tant qu'on n'est pas à la bonne place, on fait percoler le nouveau noeud vers le haut
        tabIndex[(*tas).tab[parent].noeud] = fils; 
        tabIndex[(*tas).tab[fils].noeud] = parent; 
        swapNoeud(&((*tas).tab[parent]), &((*tas).tab[fils]));

        fils = parent;
        parent = ((fils+1)/2)-1;
    }
}


noeud_t popTas(tas_t *tas, int * tabIndex)
{
    noeud_t res;

    if ((*tas).size > 0)
    {
        //printf("oui2\n");
        (*tas).size--;
        res = (*tas).tab[0];
        (*tas).tab[0] = (*tas).tab[(*tas).size]; //la derniere feuille devient la racine
        if ((*tas).size > 0)
        {
            tabIndex[(*tas).tab[0].noeud] = 0;
        }
        int i = 0;
        int fg = 1;
        int fd = 2;
        while ((fg < (*tas).size) && ((((*tas).tab[i]).poids > ((*tas).tab[fd]).poids ) || ( ((*tas).tab[i]).poids > ((*tas).tab[fg]).poids )) )
        {   //tant qu'on n'est pas à la bonne place, on fait percoler la nouvelle racine vers le bas
            if ( ((*tas).tab[fg]).poids > ((*tas).tab[fd]).poids )
            {
                tabIndex[(*tas).tab[fd].noeud] = i; 
                tabIndex[(*tas).tab[i].noeud] = fd; 
                swapNoeud(&((*tas).tab[fd]), &((*tas).tab[i]));
                i = fd;
                fg = 2*(i+1)-1;
                fd = 2*(i+1);
            }
            else 
            {
                tabIndex[(*tas).tab[fg].noeud] = i; 
                tabIndex[(*tas).tab[i].noeud] = fg; 
                swapNoeud(&((*tas).tab[fg]), &((*tas).tab[i]));
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
/*
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
*/