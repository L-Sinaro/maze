#include "game-engine.h"


Objet_t initiateObject(int height)
{
    Objet_t object;
    object.probabilitesDePresence = malloc(height*sizeof(float));
    object.zoom = 0;
    return object;
}


Objet_t * initiateObjects(int height)
{
    Objet_t * objects = malloc(TAILLE*sizeof(Objet_t));
    int i, j;

    if (objects)
    {
        for (i=0; i<TAILLE; i++)
        {
            objects[i] = initiateObject(height);
            switch (i)
            {
            case VIDE:
                objects[i].zoom = 0;
                break;

            case ENNEMI:
                objects[i].zoom = 1;
                for (j=0; j<height; j++)
                {
                    objects[i].probabilitesDePresence[j] = 0.1;
                }
                break;
            
            case BONUS:
                objects[i].zoom = 1;
                for (j=0; j<height; j++)
                {
                    objects[i].probabilitesDePresence[j] = 0.05;
                }
                break;
            
            default:
                printf("Error : initiate objects not working\n");
                break;
            }
        }
    }

    return objects;
}


void freeObject(Objet_t object)
{
    free(object.probabilitesDePresence);
}

void freeObjects(Objet_t * objects)
{
    int i;
    for (i=0; i<TAILLE; i++)
    {
        freeObject(objects[i]);
    }
}

void freeGrid(enum type ** grid, int height)
{
    int i = 0;
    if (grid)
    {
        while(i<height)
        {
            free(grid[i]);
            i++;
        }
        free(grid);
    }
}


enum type ** allocateGrid(int width, int height)
{
    enum type ** grid;
    int i=0;

    grid = calloc(height, sizeof(enum type*));

    // Si le tableau de pointeur s'est bien affecté
    if (grid)
    {
        do
        {
            // On initialise chaque ligne du tableau à 0
            grid[i] = calloc(width,sizeof(grid[0]));
        } while (grid[i] && ++i<height);
        // Tant que l'affectation s'est bien déroulé

        // Si la dernière ligne n'a pas correctement été allouée
        if (!grid[height-1])
        {
            freeGrid(grid, i); // On libère la mémoire qui a été allouée
        }
    }

    return grid;
}


void resetGrid(enum type ** grid, int width, int height)
{
    int i, j;
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            grid[i][j] = VIDE;
        }
    }
}



void displayGrid(enum type ** grid, int width, int height, int iterateurRotor)
{
    int i, j;
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            if (grid[i][(j+iterateurRotor)%width])
            {
                printf(" %d ", grid[i][(j+iterateurRotor)%width]);
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
    for (j=0; j<width; j++)
    {
        printf("---");
    }
    printf("\n");
}

void ramdomizeNewColumn(enum type ** grid, int width, int height ,int iterateurRotor, Objet_t * objects)
{
    int i, j;
    // Foreach element of the column
    for (i=0; i<height; i++)
    {
        grid[i][iterateurRotor%width] = 0;
        j=0;
        while (j<TAILLE && grid[i][iterateurRotor%width] == 0)
        {
            if ((float)rand()/((float)RAND_MAX) < objects[j].probabilitesDePresence[i])
            {
                grid[i][iterateurRotor%width] = j;
            }
            j++;
        }
    }
}


// int main()
// {
//     int iterateurRotor = 0;
//     enum type ** grid;
//     Objet_t * objects = NULL;
//     int width = 20;
//     int height = 10;

    

//     srand(time(NULL));

//     grid = allocateGrid(width, height);

//     if (!grid)
//     {
//         exit(0);
//     }

    // objects = initiateObjects(height);

    // if (objects == NULL)
    // {
    //     exit(0);
    // }

    // int i = 0;
    // while (i<10)
    // {
    //     displayGrid(grid, width, height, iterateurRotor);
    //     ramdomizeNewColumn(grid, width, height, iterateurRotor, objects);
    //     iterateurRotor++;
    //     sleep(1);
    //     i++;
    // }

    // freeObjects(objects);
    // freeGrid(grid, height);
    

//     return 0;
// }