#include "game-of-life.h"


void freeGrid(bool ** grid, int height)
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


bool ** allocateGrid(int width, int height)
{
    bool ** grid;
    int i=0;

    grid = calloc(height, sizeof(bool*));

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





void initializeGridRandomly(bool ** grid, int width, int height)
{
    int i, j;
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            if (rand() < RAND_MAX / 5)
            {
                grid[i][j] = true;
            }
            else
            {
                grid[i][j] = false;
            }   
        }
    }
}

void initializeGridWithAGlider(bool ** grid)
{
    grid[2][2] = true;
    grid[2][3] = true;
    grid[2][4] = true;
    grid[1][4] = true;
    grid[0][3] = true;
}



void displayGrid(bool ** grid, int width, int height)
{
    int i, j;
    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            if (grid[i][j])
            {
                printf(" 1 ");
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



int numberOfNeighbours(bool ** grid, int i, int j, int width, int height)
{
    int sum = 0;
    int i1,j1;
    for (i1=-1; i1<=1; i1++)
    {
        for (j1=-1; j1<=1; j1++)
        {
            // Si ce n'est pas la case du "milieu" et que la case est vivante
            if((i1!=0 || j1 != 0) && grid[((height+i+i1)%height)][((width+j+j1)%width)])
            {
                sum += 1;
            }
        }
    }
    return sum;
}


void evolveGrid(bool ** old, bool ** new, bool survive[9], bool birth[9], int width, int height)
{
    int i, j;
    int n;

    for (i=0; i<height; i++)
    {
        for (j=0; j<width; j++)
        {
            n = numberOfNeighbours(old, i, j, width, height);
            if (old[i][j])
            {
                if (survive[n])
                {
                    new[i][j] = true;
                }
                else
                {
                    new[i][j] = false;
                }
            }
            else
            {
                if (birth[n])
                {
                    new[i][j] = true;
                }
                else
                {
                    new[i][j] = false;
                }
            }
            
        }
    }
}

void swapGrid(bool *** adrGrid1, bool *** adrGrid2)
{
    bool ** tmp;
    tmp = *adrGrid1;
    *adrGrid1 = *adrGrid2;
    *adrGrid2 = tmp;
}

// int main()
// {
    
//     bool ** old;
//     bool ** new;
//     int width = 20;
//     int height = 20;
//     bool survie[9] = {false, false, true, true, false, false, false, false, false};
//     bool naissance[9] ={false, false, false, true, false, false, false, false, false};
//     int i=0;
    
//     old = allocateGrid(width, height);
//     new = allocateGrid(width, height);

//     initializeGridRandomly(old, width, height);


//     if (old && new)
//     {
//         while (i<10)
//         {
//             displayGrid(old, width, height);
//             evolveGrid(old, new, survie, naissance, width, height);
//             swapGrid(&old, &new);
//             i++;
// 	    }
//     }

//     if (old)
//     {
//         freeGrid(old, height);
//     }
//     if (new)
//     {
//         freeGrid(new, height);
//     }

//     return 0;
// }