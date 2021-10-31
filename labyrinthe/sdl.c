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

SDL_Texture* loadTextureFromImage(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
{
    SDL_Surface *my_image = NULL;           
    SDL_Texture* my_texture = NULL;         

    my_image = IMG_Load(file_image_name);   

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); 
    SDL_FreeSurface(my_image);                                     
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}


Offset_t getOffset(int v)
{
    Offset_t offset;
    if (DEPART & v)
    {
        offset.i = 8;
        offset.j = 8;
    }
    else
    {
        if (ARRIVEE & v)
        {
            offset.i = 8;
            offset.j = 7;
        }
        else
        {
            switch (v)
            {      
            case NORD:
                offset.i = 0;
                offset.j = 1;
                break;
            case SUD:
                offset.i = 1;
                offset.j = 7;
                break;
            case EST:
                offset.i = 2;
                offset.j = 4;
                break;
            case OUEST:
                offset.i = 1;
                offset.j = 5;
                break;
            case NORD+SUD:
                offset.i = 3;
                offset.j = 4;
                break;
            case NORD+EST:
                offset.i = 2;
                offset.j = 2;
                break;
            case NORD+OUEST:
                offset.i = 0;
                offset.j = 0;
                break;
            case SUD+EST:
                offset.i = 0;
                offset.j = 7;
                break;
            case SUD+OUEST:
                offset.i = 1;
                offset.j = 6;
                break; 
            case EST+OUEST:
                offset.i = 0;
                offset.j = 6;
                break;  
            case NORD+SUD+EST:
                offset.i = 1;
                offset.j = 4;
                break;
            case NORD+SUD+OUEST:
                offset.i = 0;
                offset.j = 5;
                break;
            case NORD+EST+OUEST:
                offset.i = 2;
                offset.j = 1;
                break;
            case SUD+EST+OUEST:
                offset.i = 3;
                offset.j = 0;
                break;    
            case NORD+SUD+EST+OUEST:
                offset.i = 3;
                offset.j = 6;  
                break;               
            default:
                offset.i = 2;
                offset.j = 5;   
                break;
            }
        }
    }

    return offset;
}



// static void drawWalls(SDL_Renderer * renderer, SDL_Window* window, labyrinthe_t labyrinthe)
// {
//     int i, j;

//     int widthWindow, heightWindow;
//     SDL_GetWindowSize(window, &widthWindow, &heightWindow);

    
//     int widthRectangle = widthWindow / labyrinthe.colonnes;
//     int heightRectangle = heightWindow / labyrinthe.lignes;

//     for (i=0; i<labyrinthe.lignes; i++)
//     {
//         for (j=0; j<labyrinthe.colonnes; j++)
//         {
//             if (labyrinthe.tab[i][j] & NORD)
//             {
//                 SDL_RenderDrawLine(renderer, j*widthRectangle, i*heightRectangle, (j+1)*widthRectangle, i*heightRectangle);
//             }
//             if (labyrinthe.tab[i][j] & SUD)
//             {
//                 SDL_RenderDrawLine(renderer, j*widthRectangle, (i+1)*heightRectangle, (j+1)*widthRectangle, (i+1)*heightRectangle);
//             }
//             if (labyrinthe.tab[i][j] & EST)
//             {
//                 SDL_RenderDrawLine(renderer, (j+1)*widthRectangle, i*heightRectangle, (j+1)*widthRectangle, (i+1)*heightRectangle);
//             }
//             if (labyrinthe.tab[i][j] & OUEST)
//             {
//                 SDL_RenderDrawLine(renderer, j*widthRectangle, i*heightRectangle, j*widthRectangle, (i+1)*heightRectangle);
//             }
//         }
//     }
// }


static void drawTiles(SDL_Renderer * renderer, SDL_Window* window, labyrinthe_t labyrinthe)
{
    int i, j;
    SDL_Rect tile;

    SDL_Rect source;
    SDL_Rect state;
    SDL_Texture * texture = loadTextureFromImage("assets/spritesheet.png", window, renderer);
    int heightTexture = 9;
    int widthTexture = 9;

    Offset_t offset;

    SDL_QueryTexture(texture, NULL, NULL,    // Récupération des dimensions de l'image
                    &source.w, &source.h); 
    state.w = source.w / widthTexture;
    state.h = source.h / heightTexture;

    int widthWindow, heightWindow;
    SDL_GetWindowSize(window, &widthWindow, &heightWindow);

    tile.w = widthWindow / labyrinthe.colonnes;
    tile.h = heightWindow / labyrinthe.lignes;

    for (i=0; i<labyrinthe.lignes; i++)
    {
        for (j=0; j<labyrinthe.colonnes; j++)
        {
            tile.x = j*tile.w;
            tile.y = i*tile.h;
            offset = getOffset(labyrinthe.tab[i][j]);
            state.x = offset.j * source.w / widthTexture;
            state.y = offset.i * source.h / heightTexture;

            SDL_RenderCopy(renderer, texture,
                    &state,
                    &tile);  
        }
    }
}

void drawCar(SDL_Renderer * renderer, SDL_Texture * texture, SDL_Rect car, int direction)
{
    SDL_Rect source;
    SDL_Rect state;
    int xNbOfFrames = 4;
    int yNbOfFrames = 1;

    Offset_t offset;
    offset.i = 0;
    offset.j = 0;
    
    switch (direction)
    {
        case NORD:
            offset.j = 0;
            break;
        case EST:
            offset.j = 1;
            break;
        case SUD:
            offset.j = 2;
            break;
        case OUEST:
            offset.j = 3;
            break;
        default:
            perror("Erreur : Mauvaise direction drawCar\n");
    }

    SDL_QueryTexture(texture, NULL, NULL,    // Récupération des dimensions de l'image
                    &source.w, &source.h); 

    state.x = offset.j * source.w / xNbOfFrames;
    state.y = offset.i * source.h / yNbOfFrames;
    state.w = source.w / xNbOfFrames;
    state.h = source.h / yNbOfFrames;

    SDL_RenderCopy(renderer, texture,
                        &state,
                        &car);
}

void getFacteurDirection(int direction, int * facteurX, int * facteurY)
{
    switch (direction)
    {
    case NORD:
        *facteurX = 0;
        *facteurY = -1;
        break;
    case SUD:
        *facteurX = 0;
        *facteurY = 1;
        break;
    case EST:
        *facteurX = 1;
        *facteurY = 0;
        break;
    case OUEST:
        *facteurX = -1;
        *facteurY = 0;
        break;
    }
}


void accelerateCar(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * texture, SDL_Rect * car,  labyrinthe_t labyrinthe, int direction)
{
    int i;
    int xDepart = car->x;
    int yDepart = car->y;
    int nb_pas = 10;
    int facteurX, facteurY;
    getFacteurDirection(direction, &facteurX, &facteurY);
    for (i = 0; i<nb_pas/2; i++)
    {
        car->x = xDepart + facteurX*(1 - cos(i*M_PI/nb_pas)) * car->w/2;
        car->y = yDepart + facteurY*(1 - cos(i*M_PI/nb_pas)) * car->h/2;
        drawTiles(renderer, window, labyrinthe);
        drawCar(renderer, texture, *car, direction);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(20);
    }
}


void decelerateCar(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * texture, SDL_Rect * car,Coordonnees_t position, labyrinthe_t labyrinthe, int direction)
{
    
    int i;
    int xDepart = car->w * position.j;
    int yDepart = car->h * position.i;
    int nb_pas = 10;
    int facteurX, facteurY;
    getFacteurDirection(direction, &facteurX, &facteurY);

    for (i = nb_pas/2; i<nb_pas; i++)
    {
        car->x = xDepart + facteurX*(1 - cos(i*M_PI/nb_pas)) * car->w/2;
        car->y = yDepart + facteurY*(1 - cos(i*M_PI/nb_pas)) * car->h/2;
        drawTiles(renderer, window, labyrinthe);
        drawCar(renderer, texture, *car, direction);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(20);
    }
    // printf("%d %d, %d %d \n", car->x, car->y, xDepart + car->w, yDepart + car->h);
}

void moveCarForward(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * texture, SDL_Rect * car, labyrinthe_t labyrinthe, int direction)
{
    int i;
    int nb_pas = 3; // 10 / M_PI

    int facteurX, facteurY;
    getFacteurDirection(direction, &facteurX, &facteurY);
    for (i = 0; i<nb_pas; i++)
    {
        car->x += facteurX * car->w/nb_pas;
        car->y += facteurY * car->h /nb_pas;
        drawTiles(renderer, window, labyrinthe);
        drawCar(renderer, texture, *car, direction);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(20);
    }
    printf("SPEED\n");
}


static int carHasArrived(labyrinthe_t labyrinthe, Coordonnees_t carPosition)
{
    return labyrinthe.tab[carPosition.i][carPosition.j] & ARRIVEE;
}


int getDirection(Coordonnees_t position, Coordonnees_t position_suivante)
{
    int direction; 

    if (position.i == position_suivante.i)
    {
        if (position.j < position_suivante.j)
        {
            direction = EST;
        }
        else
        {
            direction = OUEST;
        }
    }
    else
    {
        if (position.i < position_suivante.i)
        {
            direction = SUD;
        }
        else
        {
            direction = NORD;
        }       
    }
    return direction;   
}


void affiche_reussite(SDL_Color color,TTF_Font * font, SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_Surface* text_surface = NULL;
    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte 

    int windowHeight, windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    SDL_Rect pos = {0, 0, 0, 0};                                         // rectangle où le texte va être prositionné

    text_surface = TTF_RenderText_Blended(font, "You win", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte
    pos.x = (windowWidth - pos.w)/2;
    pos.y = (windowHeight - pos.h)*0.4;

    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer

    text_surface = TTF_RenderText_Blended(font, "Press R to play again", color); // création du texte dans la surface 
    if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte
    pos.x = (windowWidth - pos.w)/2;
    pos.y = (windowHeight - pos.h)*0.7;
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer

    SDL_DestroyTexture(text_texture);                                    // On n'a plus besoin de la texture avec le texte
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien
}



void playGame()
{
    SDL_Window* window = NULL;               
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;  

    int lignes = 10;
    int colonnes = 20;

    graphe_t graphe;
    labyrinthe_t labyrinthe = *initLabyrintheAleatoireSansCycle(lignes, colonnes, &graphe);
    // labyrinthe = *initLabyrinthePLein(lignes, colonnes);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "Error : Couldn't initialize SDL", window, renderer);
    if (TTF_Init() < 0) end_sdl(0, "Error : Couldn't initialize SDL TTF", window, renderer);

    int windowWidth = 1000;
    int windowHeight = 500;
   
    window = SDL_CreateWindow(
        "Jeu",                    
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,                              
        SDL_WINDOW_RESIZABLE);                 
    if (window == NULL) end_sdl(0, "Error : SDL window creation", window, renderer);

    renderer = SDL_CreateRenderer(
           window, 
           -1, 
           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "Error : SDL renderer creation", window, renderer);

    font = TTF_OpenFont("./fonts/Some-Time-Later.ttf", 100);
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);


    Coordonnees_t depart = gerererCoordonneesAleatoires(labyrinthe);
    Coordonnees_t arrivee = gerererCoordonneesAleatoires(labyrinthe);
    while (depart.i == arrivee.i && depart.j == arrivee.j)
    {
        arrivee = gerererCoordonneesAleatoires(labyrinthe);
    }
    labyrinthe.tab[depart.i][depart.j] += DEPART; 
    labyrinthe.tab[arrivee.i][arrivee.j] += ARRIVEE;



    SDL_Texture * carTexture = loadTextureFromImage("assets/Voiture_stylax.png", window, renderer);
    
    Coordonnees_t carPosition;
    carPosition.i = depart.i;
    carPosition.j = depart.j;

    SDL_Rect car;
    car.w = windowWidth/labyrinthe.colonnes;
    car.h = windowHeight/labyrinthe.lignes;
    car.x = carPosition.j * car.w;
    car.y = carPosition.i * car.h;

    int direction = SUD;


    SDL_bool program_on = SDL_TRUE;
    SDL_bool paused = SDL_FALSE;
    SDL_bool win = SDL_FALSE;

    // Render first frame
    SDL_SetRenderDrawColor(renderer,139,181,74,255);
    drawTiles(renderer, window, labyrinthe);
    drawCar(renderer, carTexture, car, SUD);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    SDL_Color textColor = {0,0,0,255};

    SDL_Event event;


    while (program_on) 
    {                                
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        // Si la dimension de la fenetre a changé :
        if (car.w != windowWidth/labyrinthe.colonnes || car.h != windowHeight/labyrinthe.lignes)
        {
            car.w = windowWidth/labyrinthe.colonnes;
            car.h = windowHeight/labyrinthe.lignes;
            car.x = carPosition.j * car.w;
            car.y = carPosition.i * car.h;
            drawTiles(renderer, window, labyrinthe);
            drawCar(renderer, carTexture, car, direction);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }

        while (program_on && SDL_PollEvent(&event)) 
        {                  
            switch (event.type) {
            case SDL_QUIT:                              
                program_on = SDL_FALSE;                    
                break;
            case SDL_KEYDOWN:                             
                             
                switch (event.key.keysym.sym) 
                {             
                    case SDLK_p:
                    case SDLK_SPACE:
                        if (!win)
                        {
                            paused = !paused;
                        }
                        break;
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        program_on = 0;                                         
                        break;
                    case SDLK_r:
                        if (win)
                        {
                            win = SDL_FALSE;
                            labyrinthe.tab[depart.i][depart.j] -= DEPART;
                            labyrinthe.tab[arrivee.i][arrivee.j] -= ARRIVEE;
                            depart = arrivee;
                            while (depart.i == arrivee.i && depart.j == arrivee.j)
                            {
                                arrivee = gerererCoordonneesAleatoires(labyrinthe);
                            }
                            labyrinthe.tab[depart.i][depart.j] += DEPART; 
                            labyrinthe.tab[arrivee.i][arrivee.j] += ARRIVEE;
                            drawTiles(renderer, window, labyrinthe);
                            drawCar(renderer, carTexture, car, direction);
                            SDL_RenderPresent(renderer);
                            SDL_RenderClear(renderer);
                        }
                        break; 
                    case SDLK_UP:    
                        if (carPosition.i > 0 && !(labyrinthe.tab[carPosition.i][carPosition.j] & NORD) && (!paused) && !(win))
                        {
                            direction = NORD;
                            accelerateCar(window, renderer, carTexture,&car, labyrinthe,direction);
                            decelerateCar(window, renderer, carTexture,&car,carPosition,labyrinthe,direction);
                            carPosition.i--;
                            car.x = carPosition.j* car.w;
                            car.y = carPosition.i* car.h;                                                        
                        }                           
                        break;

                    case SDLK_DOWN:
                        if (carPosition.i+1 < labyrinthe.lignes && !(labyrinthe.tab[carPosition.i][carPosition.j] & SUD) &&(!paused) && !(win))
                        {  
                            direction = SUD;
                            accelerateCar(window, renderer, carTexture,&car,labyrinthe,direction);
                            decelerateCar(window, renderer, carTexture,&car,carPosition,labyrinthe,direction);
                            carPosition.i++;
                            car.x = carPosition.j* car.w;
                            car.y = carPosition.i* car.h;                                                              
                        }                          
                        break;

                    case SDLK_LEFT:    
                        if (carPosition.j > 0 && !(labyrinthe.tab[carPosition.i][carPosition.j] & OUEST) && (!paused) && !(win))
                        {
                            // moveCar(window, renderer, carTexture, &car, carPosition, labyrinthe, OUEST);
                            direction = OUEST;
                            accelerateCar(window, renderer, carTexture,&car,labyrinthe,direction);
                            decelerateCar(window, renderer, carTexture,&car,carPosition,labyrinthe,direction);
                            
                            carPosition.j--;   
                            car.x = carPosition.j* car.w;
                            car.y = carPosition.i* car.h;                                                            
                        }                           
                        break;

                    case SDLK_RIGHT:    
                        if (carPosition.j+1 < labyrinthe.colonnes && !(labyrinthe.tab[carPosition.i][carPosition.j] & EST) && (!paused) && !(win))
                        {
                            // moveCar(window, renderer, carTexture, &car, carPosition, labyrinthe, EST);
                            direction = EST;
                            accelerateCar(window, renderer, carTexture,&car,labyrinthe,direction);
                            decelerateCar(window, renderer, carTexture,&car,carPosition,labyrinthe,direction);
                            carPosition.j++;    
                            car.x = carPosition.j* car.w;
                            car.y = carPosition.i* car.h;                                                         
                        }                          
                        break;
                    default:                                    
                        printf("Wrong input\n");
                        break;
                }
            break;
            }
        }
        
        if (carHasArrived(labyrinthe, carPosition))
        {
            win = SDL_TRUE;
            affiche_reussite(textColor, font, window, renderer);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }
    }
    IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
}






void parcoursPlusCoursCheminAutomatique()
{
    SDL_Window* window = NULL;               
    SDL_Renderer* renderer = NULL;

    int lignes = 10;
    int colonnes = 20;

    graphe_t graphe;
    labyrinthe_t labyrinthe = *initLabyrintheAleatoire(lignes, colonnes, 0.6, &graphe);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "Error : Couldn't initialize SDL", window, renderer);

    int windowWidth = 1000;
    int windowHeight = 500;
   
    window = SDL_CreateWindow(
        "Jeu",                    
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,                              
        SDL_WINDOW_RESIZABLE);                 
    if (window == NULL) end_sdl(0, "Error : SDL window creation", window, renderer);

    renderer = SDL_CreateRenderer(
           window, 
           -1, 
           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "Error : SDL renderer creation", window, renderer);


    Coordonnees_t depart = gerererCoordonneesAleatoires(labyrinthe);
    Coordonnees_t arrivee = gerererCoordonneesAleatoires(labyrinthe);
    while (depart.i == arrivee.i && depart.j == arrivee.j)
    {
        arrivee = gerererCoordonneesAleatoires(labyrinthe);
    }
    labyrinthe.tab[depart.i][depart.j] += DEPART; 
    labyrinthe.tab[arrivee.i][arrivee.j] += ARRIVEE;


    SDL_Texture * carTexture = loadTextureFromImage("assets/Voiture_stylax.png", window, renderer);
    
    Coordonnees_t carPosition;
    carPosition.i = depart.i;
    carPosition.j = depart.j;

    SDL_Rect car;
    car.w = windowWidth/labyrinthe.colonnes;
    car.h = windowHeight/labyrinthe.lignes;
    car.x = carPosition.j * car.w;
    car.y = carPosition.i * car.h;

    int direction = SUD;

    cellule_t * liste = plus_court_chemin_djikstra(getValueFromCoordonnees(depart, labyrinthe), getValueFromCoordonnees(arrivee, labyrinthe), graphe);
    cellule_t * cour = liste->suiv;

    Coordonnees_t nextPosition = getCoordonneesFromGraphe(cour->valeur, labyrinthe);

    SDL_bool program_on = SDL_TRUE;
    SDL_bool paused = SDL_FALSE;

    SDL_SetRenderDrawColor(renderer,139,181,74,255);

    SDL_Event event;

    while (program_on) 
    {                                
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        // Si la dimension de la fenetre a changé :
        if (car.w != windowWidth/labyrinthe.colonnes || car.h != windowHeight/labyrinthe.lignes)
        {
            car.w = windowWidth/labyrinthe.colonnes;
            car.h = windowHeight/labyrinthe.lignes;
            car.x = carPosition.j * car.w;
            car.y = carPosition.i * car.h;
            drawTiles(renderer, window, labyrinthe);
            drawCar(renderer, carTexture, car, direction);
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }

        while (program_on && SDL_PollEvent(&event)) 
        {                  
            switch (event.type) {
            case SDL_QUIT:                              
                program_on = SDL_FALSE;                    
                break;
            case SDL_KEYDOWN:                             
                             
                switch (event.key.keysym.sym) 
                {             
                    case SDLK_p:
                    case SDLK_SPACE:
                        paused = !paused;
                        break;
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        program_on = 0;                                         
                        break;
                    default:                                    
                        printf("Wrong input\n");
                        break;
                }
            break;
            }
        }

        if (!paused)
        {
            direction = getDirection(carPosition, nextPosition);
            accelerateCar(window, renderer, carTexture, &car,labyrinthe, direction);
            // if (cour->suiv && cour->suiv->suiv && direction == getDirection(nextPosition, getCoordonneesFromGraphe(cour->suiv->suiv->valeur, labyrinthe)))
            // {
            //     SDL_Delay(1000);
            //     moveCarForward(window, renderer, carTexture, &car, labyrinthe, direction);
            //     SDL_Delay(1000);
            //     carPosition = nextPosition;
            //     nextPosition = getCoordonneesFromGraphe(cour->suiv->valeur, labyrinthe);
            //     cour = cour->suiv;

            // }
            decelerateCar(window, renderer, carTexture, &car, carPosition,labyrinthe, direction);
            
            
            carPosition = nextPosition;
            
            cour = cour->suiv;

            if (carHasArrived(labyrinthe, carPosition))
            {
                // libere_ls(liste);

                labyrinthe.tab[depart.i][depart.j] -= DEPART; 
                labyrinthe.tab[arrivee.i][arrivee.j] -= ARRIVEE;

                depart = arrivee;
                while (depart.i == arrivee.i && depart.j == arrivee.j)
                {
                    arrivee = gerererCoordonneesAleatoires(labyrinthe);
                    
                }
                labyrinthe.tab[depart.i][depart.j] += DEPART; 
                labyrinthe.tab[arrivee.i][arrivee.j] += ARRIVEE;
                
                liste = plus_court_chemin_djikstra(getValueFromCoordonnees(depart, labyrinthe), getValueFromCoordonnees(arrivee, labyrinthe), graphe);
                cour = liste->suiv;

                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

            nextPosition = getCoordonneesFromGraphe(cour->valeur, labyrinthe);
            
        }
    }

    // libere_ls(liste);
    IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
}