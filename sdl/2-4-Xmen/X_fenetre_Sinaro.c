//gcc X_fenetre_Sinaro.c -o Sinaro_X_fenetre -lSDL2 -Wall -Wextra

#include <SDL2/SDL.h>
#include <stdio.h>


void renderBlack(SDL_Window * fenetre, SDL_Renderer * renderer)
{
    renderer = SDL_CreateRenderer(
           fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

SDL_Window ** creationFenetres(int nombre, int hauteurEcran)
{
    SDL_Window ** fenetres;
    SDL_Renderer* renderer = NULL;
    int i;
    int x;
    int y;
    int mid;

    mid = (nombre/2);

    fenetres = malloc(sizeof(SDL_Window *)*nombre);
    /* Creation de la premiere fenetre en haut a gauche */
    fenetres[0] = SDL_CreateWindow(
            "croix",
            0,0,
            300, 300,                               
            SDL_WINDOW_RESIZABLE);

    renderBlack(fenetres[0], renderer);

    if (fenetres[0] == NULL) 
        {
            SDL_Log("Error : SDL window 0 creation - %s\n", SDL_GetError());   
            SDL_Quit();
            exit(EXIT_FAILURE);
        }  

    for (i=1;i<mid;i++)
    {
        
        /* Creation des autres fenetres de la premiere diagonale en fonction de la position de la precedente */
        SDL_GetWindowPosition(fenetres[i-1], &x, &y);
        fenetres[i] = SDL_CreateWindow(
            "croix",
            x+110,y+50,
            300, 300,                              
        SDL_WINDOW_RESIZABLE);

        if (fenetres[i] == NULL) 
        {
            SDL_Log("Error : SDL window %d creation - %s\n", i+1, SDL_GetError());   // échec de la création de la fenêtre
            SDL_Quit();
            exit(EXIT_FAILURE);
        }  
        renderBlack(fenetres[i], renderer);       
    }

    /* Creation de la fenetre en bas a gauche*/

    fenetres[mid] = SDL_CreateWindow(
        "Croix",
        0,(hauteurEcran-200),
        300, 300,                              
        SDL_WINDOW_RESIZABLE);
    /* Gestion de l'echec de creation de la fenetre */
    if (fenetres[mid] == NULL) 
    {
        SDL_Log("Error : SDL window %d creation - %s\n", mid,SDL_GetError());   
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderBlack(fenetres[mid], renderer);  

    for (i=(mid+1);i<nombre;i++)
        {
            /* Creation des autres fenetres de la deuxieme diagonale en fonction de la position de la precedente */
            SDL_GetWindowPosition(fenetres[i-1], &x, &y);
            fenetres[i] = SDL_CreateWindow(
            "Croix",
            x+110,y-50,
            300, 300,                               
            SDL_WINDOW_RESIZABLE);
            /* Gestion de l'echec de creation de la fenetre */
            if (fenetres[i] == NULL) 
            {
                SDL_Log("Error : SDL window %d creation - %s\n", i+1, SDL_GetError());   // échec de la création de la fenêtre
                SDL_Quit();
                exit(EXIT_FAILURE);
            }
            renderBlack(fenetres[i], renderer);  

            SDL_Delay(10);       
        }  
    
    return fenetres;
}

void descenteFenetres(SDL_Window ** fenetres, int nombre, int hauteurEcran)
{
    int i;
    int timeout;
    timeout = SDL_GetTicks() + 5000;
    int xi1;
    int yi1;
    int xi2;
    int yi2;
    int mid;

    mid = nombre/2;

    do
    {
        for (i=0;i<mid;i++) /* On travaille simultanement sur les fenetres symétriques par rapport a l'axe vertical */
        {
            
            SDL_GetWindowPosition(fenetres[(mid-1)-i], &xi1, &yi1);
            SDL_GetWindowPosition(fenetres[(mid)+i], &xi2, &yi2);
            if ((yi1 < (hauteurEcran-200)) && (yi2 < (hauteurEcran-200))) /* On fait descendre les fenetres s'ils sont pas deja en bas */ 
            {
                
                SDL_SetWindowPosition(fenetres[(mid-1)-i], xi1, yi1+50); /* On descend les deux fenetres de 50 pixels */
                SDL_SetWindowPosition(fenetres[(mid)+i], xi2, yi2+50);

                SDL_Delay(2);
            }
        }
    }
    /* Jusqu'a ce que le temps soit écoulé*/
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)); 
    SDL_Delay(100);
}

void fermetureFenetres(SDL_Window ** fenetres, int nombre)
{
    int i;

    for (i=00;i<nombre;i++)
    {
        SDL_DestroyWindow(fenetres[i]);
    }
}

int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;
    SDL_Window ** fenetres;
    int hauteurEcran;
    int nbFenetres = 32;

    /* Initialisation de la SDL et gestion de l'échec */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    hauteurEcran = DM.h;
    
    fenetres = creationFenetres(nbFenetres, hauteurEcran);
    descenteFenetres(fenetres, nbFenetres, hauteurEcran); 
    fermetureFenetres(fenetres, nbFenetres);


    SDL_Quit();
    return 0;
}