#include "jeu-de-la-vie-sinaro.h"
#include "sdl.h"


void drawRectangles(SDL_Window * window, SDL_Renderer * renderer, int ** tab, int colonnes, int lignes)
{
    SDL_Rect rectangle;
    int i;
    int j;

    int widthWindow;
    int heightWindow;

    SDL_GetWindowSize(window, &widthWindow, &heightWindow); 

    int widthRectangle = widthWindow / colonnes;
    int heightRectangle = heightWindow / lignes; //les dimensions des cases en fonction de la taille de la fenetre et de la grille

    rectangle.h = widthRectangle;
    rectangle.w = heightRectangle;
    for (i=0; i<lignes; i++)
    {
        for (j=0; j<colonnes; j++)
        {
            if(tab[i][j]) //on dessine les cases vivantes
            {
              rectangle.x = j*widthRectangle;
              rectangle.y = i*heightRectangle;
              SDL_SetRenderDrawColor(renderer,                                
                                  255, 215, 0,  // mode Red, Green, Blue (tous dans 0..255)
                                  255);
              SDL_RenderFillRect(renderer, &rectangle);
            }
        }
    }
}

void vie(int ** oldTab, int x, int y, int colonnes, int lignes, int ws, int hs)
{
    int i;
    int j;

    j = x*colonnes/ws;
    i = y*lignes/hs;
    oldTab[i][j] = 1;
}

void mort(int ** oldTab, int x, int y, int colonnes, int lignes, int ws, int hs)
{
    int i;
    int j;

    j = x*colonnes/ws;
    i = y*lignes/hs;
    oldTab[i][j] = 0;
}

int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;
  
    SDL_Window   * window   = NULL;
    SDL_Renderer * renderer = NULL; 

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
  
    /* Création de la fenêtre*/
    window = SDL_CreateWindow(
        "Jeu de la vie",                        // codage en utf8, donc accents possibles
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,                                  // coin haut gauche en haut gauche de l'écran
        800, 800,                              // largeur, hauteur
        SDL_WINDOW_RESIZABLE);                 // redimensionnable
  
    if (window == NULL) 
    {
        SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    /* Création du renderer*/
    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) 
    {
        SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());   // échec de la création du renderer
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    int ** oldTab;
    int ** newTab;
    int colonnes = 20;
    int lignes = 20;
    int x; //pour la position de la souris
    int y;
    

    oldTab = initialisationGrille(colonnes, lignes);
    if (!oldTab)
    {
        SDL_Log("Error : grid allocation of oldTab has failed\n");   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE); 
    }
    
    newTab = initialisationGrille(colonnes, lignes);
    if (!newTab)
    {
        SDL_Log("Error : grid allocation of newTab has failed\n");   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    initialisationExemple(oldTab);
    SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer                          // Booléen pour dire que le programme doit continuer
    SDL_bool paused = SDL_FALSE;

    while (program_on) 
  {                              // La boucle des évènements
    SDL_Event event;                                // Evènement à traiter

    while (program_on && SDL_PollEvent(&event)) 
    {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                    // terminé le programme Défiler l'élément en tête de file dans 'event'
      switch (event.type) 
      {                         // En fonction de la valeur du type de cet évènement
        case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
          program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
          break;
        case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                      // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                      // l'event, plusieurs champs deviennent pertinents   
          switch (event.key.keysym.sym) 
          {             // la touche appuyée est ...
          case SDLK_p:                                // 'p'
          case SDLK_SPACE:                            // 'SPC'
            paused = !paused;                         // basculement pause/unpause
            break;
          case SDLK_ESCAPE:                           // 'ESCAPE'  
          case SDLK_q:                                // 'q'
            program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
            break;
          default:                                    // Une touche appuyée qu'on ne traite pas
            break;
          }
          break;
        case SDL_MOUSEBUTTONDOWN:                     // Click souris   
          if (SDL_GetMouseState(&x, &y) & 
              SDL_BUTTON(SDL_BUTTON_LEFT) ) 
          {         // Si c'est un click gauche
            vie(oldTab, x, y, 20, 20, 800, 800);       // Fonction à éxécuter lors d'un click gauche
          } 
          else if (SDL_GetMouseState(&x, &y) & 
                     SDL_BUTTON(SDL_BUTTON_RIGHT) ) 
          { // Si c'est un click droit
            mort(oldTab, x, y, 20, 20, 800, 800);          // Fonction à éxécuter lors d'un click droit
          }
          break;
        default:                                      // Les évènements qu'on n'a pas envisagé
          break;
      }
    }
    SDL_SetRenderDrawColor(renderer,0,0,0,255); 
    SDL_RenderClear(renderer);
    drawRectangles(window, renderer, oldTab, colonnes, lignes);
    SDL_RenderPresent(renderer);        // On redessine
    if (!paused) 
    {                                  // Si on n'est pas en pause
      transition(oldTab, newTab, colonnes, lignes);             // la vie continue... 
      echangeTab(&oldTab, &newTab);
    }
    SDL_Delay(100);                                  // Petite pause
  }  

    // Free the grids that were allocated
    libereGrille(oldTab, lignes);
    libereGrille(newTab, lignes);

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}