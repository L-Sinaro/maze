//gcc textes.c -o texte -lSDL2 -lSDL2_ttf -Wall -Wextra

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h> 

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
  TTF_Quit();                                                      

  if (!ok) 
  {                                                      
         exit(EXIT_FAILURE);                                              
  }                                                               
}

int main()
{

       SDL_Window* window = NULL; 
       SDL_Renderer* renderer = NULL;

       window = SDL_CreateWindow(
       "evenement",                    // codage en utf8, donc accents possibles
       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,                                  // coin haut gauche en haut gauche de l'écran
       800, 600,                              // largeur = 800, hauteur = 600
       SDL_WINDOW_RESIZABLE);                 // redimensionnable

       if (window == NULL) 
       {
              SDL_Log("Error : SDL window creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
              SDL_Quit();
              exit(EXIT_FAILURE);
       }

       renderer = SDL_CreateRenderer(
              window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

       if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
       SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
       SDL_RenderClear(renderer);

if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);

TTF_Font* font = NULL;                                               // la variable 'police de caractère'
font = TTF_OpenFont("Pacifico.ttf", 65);                     // La police à charger, la taille désirée
if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

TTF_SetFontStyle(font, 0);           // en italique, gras

SDL_Color color = {0, 250, 0, 255};                                  // la couleur du texte
SDL_Surface* text_surface = NULL;                                    // la surface  (uniquement transitoire)
text_surface = TTF_RenderText_Blended(font, "Bonsoir", color); // création du texte dans la surface 
if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien

SDL_Rect pos = {0, 0, 0, 0};                                         // rectangle où le texte va être prositionné
SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer   
SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte

SDL_RenderPresent(renderer);                                         // Affichage 

//TTF_Quit();  
       SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer                          // Booléen pour dire que le programme doit continuer
      SDL_bool paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
while (program_on) {                              // La boucle des évènements
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
      switch (event.key.keysym.sym) {             // la touche appuyée est ...
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
      if (SDL_GetMouseState(NULL, NULL) & 
          SDL_BUTTON(SDL_BUTTON_LEFT) ) {         // Si c'est un click gauche
        //change_state(state, 1, window);           // Fonction à éxécuter lors d'un click gauche
      } else if (SDL_GetMouseState(NULL, NULL) & 
                 SDL_BUTTON(SDL_BUTTON_RIGHT) ) { // Si c'est un click droit
        //change_state(state, 2, window);           // Fonction à éxécuter lors d'un click droit
      }
      break;
    default:                                      // Les évènements qu'on n'a pas envisagé
      break;
    }
  }
  //draw(state, &color, renderer, window);          // On redessine
  //if (!paused) {                                  // Si on n'est pas en pause
  //  next_state(state, survive, born);             // la vie continue... 
  //}
  SDL_Delay(50);                                  // Petite pause
 }
       

       end_sdl(1, "Normal ending", window, renderer);
       return 0;

}