#include <SDL2/SDL.h>
#include <stdio.h>

/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*                                             Création et deplacement d'un X fenêtré                                                   */
/*--------------------------------------------------------------------------------------------------------------------------------------*/


void Creation_X_fenetre(SDL_Window ** window)
{
    int i;
                                                                                    /*              Partie 1 de la croix               */
    for (i=0;i<16;i++)
    {
        if ( i == 0) 
        {
                                                                                    /* Creation de la premiere fenetre en haut a gauche*/

            window[i] = SDL_CreateWindow(
            "Fenêtre",
            0,0,
            300, 300,                               
            SDL_WINDOW_RESIZABLE);

                                                                                    /*   Gestion de l'echec de creation de la fenetre  */

            if (window[i] == NULL) 
            {
                SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   
                SDL_Quit();
                exit(EXIT_FAILURE);
            }  
        }
        else 
        {
                                                                                    /*  Creation des autres fenetres de la branche en  */
                                                                                    /*    fonction de la position de la precedente     */
            int x;
            int y;

            SDL_GetWindowPosition(window[i-1], &x, &y);

            window[i] = SDL_CreateWindow(
                "Fenêtre",
                x+110,y+50,
                300, 300,                              
            SDL_WINDOW_RESIZABLE);

                                                                                    /*   Gestion de l'echec de creation de la fenetre  */

            if (window[i] == NULL) 
            {
                SDL_Log("Error : SDL window %d creation - %s\n", i+1, SDL_GetError()); 
                SDL_Quit();
                exit(EXIT_FAILURE);
            }  
        }   

        SDL_Delay(10);        
    }
  

    for (i=16;i<32;i++)
    {
        if (i == 16)
        {

                                                                                    /*     Creation de la fenetre en bas a gauche     */

            window[i] = SDL_CreateWindow(
            "Fenêtre",
            0,780,
            300, 300,                              
            SDL_WINDOW_RESIZABLE);

                                                                                    /*   Gestion de l'echec de creation de la fenetre  */

            if (window[i] == NULL) 
            {
                SDL_Log("Error : SDL window 17 creation - %s\n", SDL_GetError());   
                SDL_Quit();
                exit(EXIT_FAILURE);
            }
        }
        else
        {
                                                                                    /*  Creation des autres fenetres de la branche en  */
                                                                                    /*    fonction de la position de la precedente     */
            int x;
            int y;

            SDL_GetWindowPosition(window[i-1], &x, &y);

            window[i] = SDL_CreateWindow(
                "Fenêtre",
                x+110,y-50,
                300, 300,                               
                SDL_WINDOW_RESIZABLE);

                                                                                    /*   Gestion de l'echec de creation de la fenetre  */

            if (window[i] == NULL) 
            {
                SDL_Log("Error : SDL window %d creation - %s\n", i+1, SDL_GetError());   
                SDL_Quit();
                exit(EXIT_FAILURE);
            }       
        }

        SDL_Delay(10);      
    } 
}

void Deplacement_fenetres(SDL_Window ** window)                                     /*       Gestion de la descente des fenetres       */ 
{
    int xdeb;
    int ydeb;
    int i;
    SDL_DisplayMode screen;                                                       /*   Initialisation d'un tableau de pointeurs de fenetres  */

    SDL_GetCurrentDisplayMode(0, &screen);

    do
    {
        for (i=0;i<16;i++)                                                          /*   On travaille simultanement sur les fenetres    */ 
                                                                                    /*        symétriques par rapport a l'axe y         */
        {
            int xi1;
            int yi1;

            int xi2;
            int yi2;
            
            SDL_GetWindowPosition(window[15-i], &xi1, &yi1);
            SDL_GetWindowPosition(window[16+i], &xi2, &yi2);
            if ((yi1 < screen.h - 300) && (yi2 < screen.h - 300))                  /* Les fenetres ne sont pas arrivees en bas de l'ecran */ 
            {
                
                SDL_SetWindowPosition(window[15-i], xi1, yi1+50);                  /*      On descend les deux fenetres de 50 pixels      */
                SDL_SetWindowPosition(window[16+i], xi2, yi2+50);

                SDL_Delay(3);
            }
        }
        SDL_GetWindowPosition(window[0], &xdeb, &ydeb);                            /*    Calcul de la position de la fenetre en haut a    */
    }                                                                              /*             gauche apres un deplacement             */
    while(SDL_GetTicks()<2000);                                                    /*           Jusqu'a la fin du temps imparti           */
}

void Fermeture_fenetres(SDL_Window ** window)
{
    int i; 

    for (i=31;i>=0;i--)
    {
        SDL_DestroyWindow(window[i]);
    }
}

int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window ** window;   
                                                                                  /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());             /*           L'initialisation de la SDL a échoué           */
        exit(EXIT_FAILURE);
    }

    window = (SDL_Window **)malloc(sizeof(SDL_Window*)*32);                       /*              Initialisation de 32 fenetres              */
    Creation_X_fenetre(window);                                                   /*                  Creation des fenetres                  */
    Deplacement_fenetres(window);                                                 /*          Gestion de la descente des fenetres            */
 
    SDL_Delay(1000);                                                              /*                    Delai de 1000 ms                     */

    Fermeture_fenetres(window);                                                   /*                 Fermeture des fenetres                  */

    SDL_Quit();
    return 0;
}
