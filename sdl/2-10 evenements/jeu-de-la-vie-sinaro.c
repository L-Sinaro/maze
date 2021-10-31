//gcc jeu-de-la-vie-sinaro.c -o sinaro_vie -Wall -Wextra
#include "jeu-de-la-vie-sinaro.h"

int survie[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0}; //les regles du jeu de la vie selon le nombre de voisins
int naissance[9] ={0, 0, 0, 1, 0, 0, 0, 0, 0};

int ** initialisationGrille(int lignes, int colonnes)
{
    int ** tab;
    int i;

    tab = malloc(sizeof(int *)*lignes);

    if (tab) //on regarde si la mémoire a bien été allouée
    {
        for (i=0; i<lignes;++i)
        {
            tab[i] = calloc(colonnes, sizeof(int));
        }
    }

    return tab;
}

void libereGrille(int ** tab, int lignes)
{
    int i;
    for (i=0; i<lignes;++i)
    {
        free(tab[i]);
    }
    free(tab);
}

void initialisationExemple(int ** tab)  //on initialise comme dans l'exemple
{
    tab[2][2] = 1;
    tab[2][3] = 1;
    tab[2][4] = 1;
    tab[1][4] = 1;
    tab[0][3] = 1;
}

void affiche(int ** tab, int lignes, int colonnes) 
{
    int i; 
    int j;

    for (i=0; i<lignes; i++)
    {
        for (j=0; j<colonnes; j++)
        {
        printf("%d ", tab[i][j]);
        }
        printf("\n");
    }

    printf("---\n");
    
}

int nbVoisins(int ** tab, int i, int j, int lignes, int colonnes) // on compte le nombre de voisins de (i,j) vivants 
{
    int cpt = 0;
    int k;
    int l;
    int x;
    int y;

    for (k=-1; k<=1; k++)
    {
        for (l=-1; l<=1; l++)
        {
            x = (lignes+i+k)%lignes; //on se place de (i,j) sur les voisins selon une structure d'anneau
            y = (colonnes+j+l)%colonnes;
            if((k!=0 || l != 0) && tab[x][y])
            {
                cpt += 1;
            }
        }
    }
    return cpt;
}

void transition(int ** oldtab, int ** newtab, int lignes, int colonnes) //on fait evoluer la grille selon les regles donnees
{
    int i;
    int j;
    int nbvivants;

    for (i=0; i<lignes; i++)
    {
        for (j=0; j<colonnes; j++)
        {
            nbvivants = nbVoisins(oldtab, i, j, colonnes, lignes);
            if (oldtab[i][j])
            {
            newtab[i][j] = survie[nbvivants]; //on ne peut pas écrire sur un seul tableau car cela fausserait la transition pour les cases d'apres 
            }
            else
            {
                newtab[i][j] = naissance[nbvivants];
            }
            
        }
    }
}

void echangeTab(int *** tab1, int *** tab2) //on se fonde sur la nouvelle grille pour la prochaine iteration
{
    int ** temp;

    temp = *tab1;
    *tab1 = *tab2;
    *tab2 = temp; 
}

/*

int main()
{
    int ** oldtab;
    int ** newtab;
    int i;
    int lignes = 10;
    int colonnes = 10;

    oldtab = initialisationGrille(10, 10);
    newtab = initialisationGrille(10, 10);
    initialisationExemple(oldtab);
    for (i=0;i<50;++i)
    {
        affiche(oldtab, lignes, colonnes);
        transition(oldtab, newtab, lignes, colonnes);
        echangeTab(&oldtab, &newtab);
    }

    libereGrille(oldtab, lignes);
    libereGrille(newtab, lignes);

    return 0;
}
*/