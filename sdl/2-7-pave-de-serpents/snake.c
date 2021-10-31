//gcc serpents.c -o serpent -lSDL2 -Wall -Wextra

#include "snake.h"

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/

int couleur_aleatoire()
{
    return (rand()%256);
}

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

void drawrect(SDL_Renderer* renderer, int i, SDL_Rect * serpent, SDL_Color * couleur, int x, int y, int w, int h) 
{                                   // Je pense que vous allez faire moins laid :)
    SDL_Rect rectangle;
                                           
    couleur[i].b = couleur_aleatoire();
    couleur[i].g = couleur_aleatoire();
    couleur[i].r = couleur_aleatoire();

    SDL_SetRenderDrawColor(renderer,                                
                              couleur[i].r, couleur[i].g, couleur[i].b,  // mode Red, Green, Blue (tous dans 0..255)
                              255);                                     // 0 = transparent ; 255 = opaque
  rectangle.x = x;                                                    // x haut gauche du rectangle
  rectangle.y = y;                                                   // y haut gauche du rectangle
  rectangle.w = w;                                                  // sa largeur (w = width)
  rectangle.h = h;                                                  // sa hauteur (h = height)

  //SDL_RenderFillRect(renderer, &rectangle);
  serpent[i] = rectangle;
  //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderDrawRect(renderer, &rectangle);
  /*SDL_RenderDrawLine(renderer,
                          0, 0,                                       // x,y du point de la première extrémité
                          400, 400);                                  // x,y seconde extrémité
                          */

}
/************************************/
/*  exemple de création de fenêtres */
/************************************/
// Snake_t createSnake(int size, enum direction direction, int x, int y)
// {
//     int i;
//     Snake_t snake;
//     snake.parts = malloc(size * sizeof(ColoredRectangle_t));
//     snake.size = size;

//     if (snake.parts)
//     {
//         for (i=0; i<size; i++)
//         {
//             snake.parts[i].color.b = couleur_aleatoire();
//             snake.parts[i].color.g = couleur_aleatoire();
//             snake.parts[i].color.r = couleur_aleatoire();
            
//             switch (direction)
//             {
//                 case UP:
//                     rectangle.x = x-i*90;                                                    // x haut gauche du rectangle
//                     rectangle.y = y+i*2.5;                                                   // y haut gauche du rectangle
//                     rectangle.w = 100;                                                  // sa largeur (w = width)
//                     rectangle.h = 50-(i*5); 
//                 break;

//                 case DOWN:
//                     rectangle.x = x+i*90;                                                    // x haut gauche du rectangle
//                     rectangle.y = y+i*2.5;                                                   // y haut gauche du rectangle
//                     rectangle.w = 100;                                                  // sa largeur (w = width)
//                     rectangle.h = 50-(i*5); 
//                 break;

//                 case LEFT:
//                     rectangle.x = x-i*90;                                                    // x haut gauche du rectangle
//                     rectangle.y = y+i*2.5;                                                   // y haut gauche du rectangle
//                     rectangle.w = 100;                                                  // sa largeur (w = width)
//                     rectangle.h = 50-(i*5); 
//                 break;

//                 case RIGHT:
//                     rectangle.x = x-i*90;                                                    // x haut gauche du rectangle
//                     rectangle.y = y+i*2.5;                                                   // y haut gauche du rectangle
//                     rectangle.w = 100;                                                  // sa largeur (w = width)
//                     rectangle.h = 50-(i*5); 
//                 break;
//             }
            
//         }
//     }
// }

void drawSerpent(SDL_Renderer* renderer, SDL_Rect ** serpent, SDL_Color ** couleur, enum direction direction)
{
    int i;

    (*couleur) = malloc(sizeof(SDL_Color)*5);
    (*serpent) = malloc(sizeof(SDL_Rect)*5);
    switch (direction)
    {
        case UP:
            for (i=0; i<5; ++i)
            {
                drawrect(renderer, i, (*serpent), (*couleur), 50-(i*90), 250+(i*2.5), 100, 50-(i*5));
            }
        break;

        case DOWN:
            for (i=0; i<5; ++i)
            {
                drawrect(renderer, i, (*serpent), (*couleur), 50+(i*90), 250+(i*2.5), 100, 50+(i*5));
            }
        break;

        case RIGHT:
            for (i=0; i<5; ++i)
            {
                drawrect(renderer, i, (*serpent), (*couleur), 350+(i*2.5), 500+(i*90), 50-(i*5), 100);
            }
        break;

        case LEFT:
            for (i=0; i<5; ++i)
            {
                drawrect(renderer, i, (*serpent), (*couleur), 350+(i*2.5), 500+(i*90), 50-(i*5), 100);
            }
        break;
    }
}


void clear(SDL_Renderer * renderer) 
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}


void draw(SDL_Renderer * renderer, SDL_Rect * rect, SDL_Color couleur) 
{
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, 255);
    SDL_RenderDrawRect(renderer, rect);
}

void moveSerpent(SDL_Renderer* renderer, SDL_Rect * serpent, SDL_Color * couleur, enum direction direction)
{
    int i;

    switch (direction)
    {
        case UP:
            for (i=0; i<5; ++i)
            {
              serpent[i].y -= 10;
              draw(renderer, &(serpent[i]), couleur[i]);
            }
        break;

        case DOWN:
            for (i=0; i<5; ++i)
            {
              serpent[i].y += 10;
              draw(renderer, &(serpent[i]), couleur[i]);
            }
        break;

        case RIGHT:
            for (i=0; i<5; ++i)
            {
              serpent[i].x += 10;
              draw(renderer, &(serpent[i]), couleur[i]);
            }
        break;

        case LEFT:
            for (i=0; i<5; ++i)
            {
              serpent[i].x -= 10;
              draw(renderer, &(serpent[i]), couleur[i]);
            }
        break;

        default:
            printf("mauvaise direction rentree\n");
    }
}


void moveGroupe(SDL_Renderer* renderer, SDL_Rect ** serpent, SDL_Color ** couleur, int pas, int numberOfSnakes)
{
  int j;

  for (j=0; j<pas; ++j)
  {
    clear(renderer);

    moveSerpent(renderer, serpent[0], couleur[0], UP);
    moveSerpent(renderer, serpent[1], couleur[1], RIGHT);
    SDL_RenderPresent(renderer);
    SDL_Delay(40);
  }
}

 
int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;        SDL_Delay(40);

    SDL_Window* window = NULL;               // Future fenêtre
    SDL_Renderer* renderer = NULL;           // Futur rendu
    SDL_Rect ** serpents;
    SDL_Color ** couleurs;

  /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

  /* Création de la fenêtre de gauche */
    window = SDL_CreateWindow(
        "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
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
           window, 
           -1, 
           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);


    int numberOfSnakes = 2;
    serpents = malloc(sizeof(SDL_Rect *)*2);
    couleurs = malloc(sizeof(SDL_Color *)*2);

    srand(time(NULL));
    drawSerpent(renderer, &(serpents[0]), &(couleurs[0]), RIGHT);
    drawSerpent(renderer, &(serpents[1]), &(couleurs[1]), UP);
    SDL_RenderPresent(renderer);
    moveGroupe(renderer, serpents, couleurs, 120, 2);
    /* Normalement, on devrait ici remplir les fenêtres... */   

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */;

    end_sdl(1, "Normal ending", window, renderer);
    return 0;
}