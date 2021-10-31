#include "sdl.h"

void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer) {                           // renderer à fermer
    char msg_formated[255];                                         
    int l;                                                          

    if (!ok) {                                                      
        strncpy(msg_formated, msg, 250);                                 
        l = strlen(msg_formated);                                        
        strcpy(msg_formated + l, " : %s\n");                     

        SDL_Log(msg_formated, SDL_GetError());                   
    }                                                               

    if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
    if (window != NULL)   SDL_DestroyWindow(window);                                        

    SDL_Quit();                                                     

    if (!ok) 
    {                                                      
        exit(EXIT_FAILURE);                                              
    }                                                               
}  

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

void affiche_iterations(char * iterations, int x, int y, SDL_Color color,TTF_Font * font, SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_Surface* text_surface = NULL;
    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte 
    SDL_Rect pos = {x, y, 0, 0};                                         // rectangle où le texte va être prositionné

    text_surface = TTF_RenderText_Blended(font, "iterations", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer
    text_surface = TTF_RenderText_Blended(font, iterations, color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
    pos.y = pos.y+pos.h*0.8;
    
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer

    SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
  
    SDL_Window   * window   = NULL;
    SDL_Renderer * renderer = NULL; 
    TTF_Font* font = NULL;                  // la variable 'police de caractère'

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);
    font = TTF_OpenFont("./fonts/Champagne _Limousines.ttf", 50);                     // La police à charger, la taille désirée
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);
    TTF_SetFontStyle(font, 0);           // en italique, gras ou non
  
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

    

    
    bool ** old;
    bool ** new;
    int width = 20;
    int height = 20;
    bool survie[9] = {false, false, true, true, false, false, false, false, false};
    bool naissance[9] ={false, false, false, true, false, false, false, false, false};
    

    old = allocateGrid(width, height);
    if (!old)
    {
        SDL_Log("Error : grid allocation of old has failed\n");   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE); 
    }
    
    new = allocateGrid(width, height);
    if (!new)
    {
        SDL_Log("Error : grid allocation of new has failed\n");   // échec de la création de la fenêtre
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    initializeGridWithAGlider(old);

    // Position du curseur de souris
    int x, y;

    int w, h;


    SDL_bool program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
             paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    int cpt = 0;
    char iterations[5];
    SDL_Color color = {255, 255, 255, 255}; 
    
    while (program_on) {                                // La boucle des évènements
        SDL_Event event;                                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) {                         // En fonction de la valeur du type de cet évènement
                case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
                break;
                case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                        // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                        // l'event, plusieurs champs deviennent pertinents   
                switch (event.key.keysym.sym) // la touche appuyée est ...
                {             
                    case SDLK_p:                                // 'p'
                    case SDLK_SPACE:                            // 'SPC'
                        paused = !paused;                         // basculement pause/unpause
                        break;
                    case SDLK_ESCAPE:                           // 'ESCAPE'  
                    case SDLK_q:                                // 'q'
                        program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
                        break;
                    default:                                    // Une touche appuyée qu'on ne traite pas
                        printf("Wrong input\n");
                        break;
                }
            break;
            case SDL_MOUSEBUTTONDOWN:                     // Click souris   
                if (SDL_GetMouseState(&x, &y) && paused) {   
                    SDL_GetWindowSize(window, &w, &h);       // Si c'est un click gauche

                    // On inverse l'état de la case cliquée
                    old[height*y/h][width*x/w] = !old[height*y/h][width*x/w];
                }
            break;
            default:                                      // Les évènements qu'on n'a pas envisagé
                
            break;
            }
        }
         
        
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        drawRectangles(window, renderer, old, width, height);
        snprintf(iterations, 5, "%d", cpt);
        affiche_iterations(iterations, 0, 0, color, font, window, renderer);
        SDL_RenderPresent(renderer);
        

        if (!paused) {                                  // Si on n'est pas en pause
            evolveGrid(old, new, survie, naissance, width, height);
            swapGrid(&old, &new);             // la vie continue... 
            ++cpt;
        }
        SDL_Delay(10);                                  // Petite pause
    }

    // Free the grids that were allocated
    freeGrid(old, height);
    freeGrid(new, height);

    TTF_Quit();

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}
