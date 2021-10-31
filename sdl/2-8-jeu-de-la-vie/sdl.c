#include "sdl.h"

static void drawRectangles(SDL_Window * window, SDL_Renderer * renderer, bool ** grid, int widthGrid, int heightGrid)
{
    SDL_Rect rectangle;
    int i, j;

    int widthWindow, heightWindow;
    SDL_GetWindowSize(window, &widthWindow, &heightWindow);

    int widthRectangle = widthWindow / widthGrid;
    int heightRectangle = heightWindow / heightGrid;

    for (i=0; i<heightGrid; i++)
    {
        for (j=0; j<widthGrid; j++)
        {
            if(grid[i][j])
            {
                rectangle.h = widthRectangle;
                rectangle.w = heightRectangle;
                rectangle.x = j*widthRectangle;
                rectangle.y = i*heightRectangle;
                SDL_SetRenderDrawColor(renderer,                                
                                    0, 255, 255,  // mode Red, Green, Blue (tous dans 0..255)
                                    255);
                SDL_RenderFillRect(renderer, &rectangle);
            }
        }
    }
}



int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
  
    SDL_Window   * window   = NULL;
    SDL_Renderer * renderer = NULL; 

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
  
    /* Création de la fenêtre*/
    window = SDL_CreateWindow(
        "Game of life",                        // codage en utf8, donc accents possibles
        0, 0,                                  // coin haut gauche en haut gauche de l'écran
        800, 800,                              // largeur, hauteur
        SDL_WINDOW_RESIZABLE);                 // redimensionnable
  
    if (window == NULL) {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    /* Création du renderer*/
    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());   // échec de la création du renderer
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    

    
    bool ** oldTab;
    bool ** newTab;
    int width = 20;
    int height = 20;
    bool survie[9] = {false, false, true, true, false, false, false, false, false};
    bool naissance[9] ={false, false, false, true, false, false, false, false, false};
    int i=0;
    

    oldTab = allocateGrid(width, height);
    if (!oldTab)
    {
        SDL_Log("Error : grid allocation of oldTab has failed\n");   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE); 
    }
    
    newTab = allocateGrid(width, height);
    if (!newTab)
    {
        SDL_Log("Error : grid allocation of newTab has failed\n");   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    initializeGridWithAGlider(oldTab);

    bool done = false;
    while (!done)
    {
        evolveGrid(oldTab, newTab, survie, naissance, width, height);
        swapGrid(&oldTab, &newTab);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer); 
        drawRectangles(window, renderer, oldTab, width, height);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    // Free the grids that were allocated
    freeGrid(oldTab, height);
    freeGrid(newTab, height);

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}