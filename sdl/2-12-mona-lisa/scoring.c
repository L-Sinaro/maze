#include "scoring.h"

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


void affiche_scorechar(char * scorechar, int x, int y, SDL_Color color,TTF_Font * font, SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_Surface* text_surface = NULL;
    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte 
    SDL_Rect pos = {x, y, 0, 0};                                         // rectangle où le texte va être prositionné

    text_surface = TTF_RenderText_Blended(font, "score", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);
      
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
    
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer

    text_surface = TTF_RenderText_Blended(font, scorechar, color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);
      
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
    pos.y = pos.y+pos.h*0.4;
    
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer

    SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien
}


void affiche_gameOver(int x, int y, SDL_Color color,TTF_Font * font, SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_Surface* text_surface = NULL;
    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte 
    SDL_Rect pos = {x, y, 0, 0};                                         // rectangle où le texte va être prositionné

    text_surface = TTF_RenderText_Blended(font, "Game Over", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 

    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer

    text_surface = TTF_RenderText_Blended(font, "Press R to play again", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte
    pos.y = pos.y+pos.h*0.7;
    pos.x = pos.x-pos.w*0.2;
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer

    SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien
}