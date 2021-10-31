#include "sdl.h"


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


void setBackground(SDL_Texture *my_texture, 
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
    SDL_Rect 
            source = {0},                         
            window_dimensions = {0},              
            destination = {0};                    

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);                    
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       

    destination = window_dimensions;              

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);
}



static void addTexturedRectangleToRenderer(SDL_Texture *my_texture, SDL_Renderer *renderer, SDL_Rect * destination) {
    SDL_Rect source = {0};
    SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image


    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    destination);                 // Création de l'élément à afficher

}


static void drawObjets(SDL_Texture * my_texture, SDL_Window* window, SDL_Renderer * renderer, enum type ** grid, int widthGrid, int heightGrid, int iterateurRotor)
{
    int i, j;
    SDL_Rect rectangle;

    int widthWindow, heightWindow;
    SDL_GetWindowSize(window, &widthWindow, &heightWindow);

    int widthRectangle = widthWindow / widthGrid;
    int heightRectangle = heightWindow / heightGrid;

    for (i=0; i<heightGrid; i++)
    {
        for (j=0; j<widthGrid; j++)
        {
            if(grid[i][(j+iterateurRotor)%widthGrid] != VIDE)
            {
                rectangle.h = widthRectangle;
                rectangle.w = heightRectangle;
                rectangle.x = j*widthRectangle;
                rectangle.y = i*heightRectangle;
                addTexturedRectangleToRenderer(my_texture, renderer, &rectangle);
            }
        }
    }
}

void convertPixeltToGrid(int x, int y, int * i, int * j, int h,int w,int wh, int ww)
{
  (*i) = y*h/wh;
  (*j) = x*w/ww;
}

SDL_bool thePlaneHasHitAnObject(SDL_Window * window, SDL_Rect plane, enum type ** grid, int gridWidth, int gridHeight, int iterateurRotor)
{
    int iBack, jBack;

    int iFront, jFront;

    int windowWidth, windowHeight;

    SDL_GetWindowSize(window,                   
                        &windowWidth, 
                        &windowHeight);

    convertPixeltToGrid(plane.x, plane.y + plane.h / 2, &iBack, &jBack, gridHeight, gridWidth, windowHeight, windowWidth);
    convertPixeltToGrid(plane.x + plane.w, plane.y + plane.h / 2, &iFront, &jFront, gridHeight, gridWidth, windowHeight, windowWidth);


    return (grid[iBack][(jBack + iterateurRotor)%gridWidth] != VIDE || grid[iFront][(jFront+iterateurRotor)%gridWidth] != VIDE);
}




int main()
{
    SDL_Window* window = NULL;               
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;  

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "Error : Couldn't initialize SDL", window, renderer);
    if (TTF_Init() < 0) end_sdl(0, "Error : Couldn't initialize SDL TTF", window, renderer);

    int windowHeight = 500;
    int windowWidth = 1000;
   
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

    font = TTF_OpenFont("./fonts/Pacifico.ttf", 40);
    if (font == NULL) end_sdl(0, "Can't load font", window, renderer);



    SDL_Texture * background = loadTextureFromImage("images/background.png", window, renderer);
    SDL_Texture * hotAirBaloon = loadTextureFromImage("images/hot-air-baloon.png", window, renderer);
    SDL_Texture * planeTexture = loadTextureFromImage("images/plane.png", window, renderer);
    // SDL_Texture * pigeon = loadTextureFromImage("images/pigeon.pgn", window, renderer);


    
    Objet_t * objects;
    enum type ** grid;
    int width = 20;
    int height = 10;
    int iterateurRotor = 0;

    srand(time(NULL));
     

    grid = allocateGrid(width, height);
    if (!grid) end_sdl(0, "Couldn't initialize grid", window, renderer);

    objects = initiateObjects(height);
    if (!objects) end_sdl(0, "Couldn't initialize grid", window, renderer);


    SDL_bool program_on = SDL_TRUE,
             paused = SDL_FALSE,
             thePlaneHasCrashed = SDL_FALSE,
             replay = SDL_TRUE;
    SDL_Color colorOfTheText = {0, 0, 0, 255};
    

    SDL_Rect plane;
    plane.h = windowHeight / 20;
    plane.w = plane.h *2;


    int jump = 15;
    int score = 0;
    char scorechar [5]; 

    int i = 0;
    
    while (program_on) 
    {                                
        SDL_Event event;                                

        while (program_on && SDL_PollEvent(&event)) 
        {                  
            switch (event.type) {                        
            case SDL_QUIT:                              
                program_on = SDL_FALSE;                    
                break;
            case SDL_KEYDOWN:                             
                                                        
                                                       
                switch (event.key.keysym.sym) 
                {             
                    case SDLK_p:                                // 'p'
                    case SDLK_SPACE:                            // 'SPC'
                        if (!thePlaneHasCrashed)
                        {
                        paused = !paused;                         // basculement pause/unpause
                        }
                        break;
                    case SDLK_ESCAPE:                           // 'ESCAPE'  
                    case SDLK_q:                                // 'q'
                        program_on = 0;                                                              
                        break;
                    case SDLK_r:
                        if (thePlaneHasCrashed)
                        {
                            replay = SDL_TRUE;
                            thePlaneHasCrashed = SDL_FALSE;
                            score = 0;
                        }
                        break; 
                    case SDLK_UP:    
                        if ((plane.y - jump >= 0) && (!paused) && !thePlaneHasCrashed)
                        {
                            plane.y -= jump;                                                            
                        }                           
                        break;

                    case SDLK_DOWN:    
                        if ((plane.y + plane.h + jump < windowHeight) && (!paused) && !thePlaneHasCrashed)
                        {
                            plane.y += jump;                                                           
                        }                          
                        break;

                    case SDLK_LEFT:    
                        if ((plane.x - jump >= 0) && (!paused) && !thePlaneHasCrashed)
                        {
                            plane.x -= jump;                                                           

                        }                           
                        break;

                    case SDLK_RIGHT:    
                        if ((plane.x + plane.w + jump < windowWidth) && (!paused) && !thePlaneHasCrashed)
                        {
                            plane.x += jump;                                                           

                        }                          
                        break;
                    default:                                    
                        printf("Wrong input\n");
                        break;
                }
            break;
            }
        }

        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        plane.h = windowHeight / 20;
        plane.w = plane.h *2;
        
        if (!replay)
        {
            if(thePlaneHasHitAnObject(window, plane, grid, width, height, iterateurRotor))
            {
                thePlaneHasCrashed = SDL_TRUE;
                
            }
            setBackground(background, window,renderer);
            drawObjets(hotAirBaloon, window, renderer, grid, width, height, iterateurRotor);

            addTexturedRectangleToRenderer(planeTexture, renderer, &plane);
            

            if (!paused && !thePlaneHasCrashed && i++>=10) {                                 
                ramdomizeNewColumn(grid, width, height, iterateurRotor, objects);
                iterateurRotor++;
                score++;
                i=0;
                snprintf(scorechar, 5, "%d", score);
            }
            affiche_scorechar(scorechar, 900, -20, colorOfTheText, font, window, renderer);
            if (thePlaneHasCrashed)
            {
                affiche_gameOver(400, 200, colorOfTheText, font, window, renderer);
            }

        }
        else
        {   
            resetGrid(grid, width, height);
            plane.x = windowWidth/3;
            plane.y = windowHeight/2;
            
            replay = SDL_FALSE;
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(30); 
    }
    freeGrid(grid, height);
    IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
    
    return 0;
}
