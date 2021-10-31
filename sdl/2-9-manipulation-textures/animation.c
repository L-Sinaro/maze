#include <SDL2/SDL_image.h>


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


SDL_Texture* loadTextureFromImage(char  *  file_image_name, 
                                     SDL_Window *window, 
                                     SDL_Renderer *renderer )
{
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void setBackground(SDL_Texture *my_texture, 
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
    SDL_Rect 
            source = {0},                         // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
            destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
                    &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
                    &source,
                    &destination);                 // Création de l'élément à afficher
    // SDL_RenderPresent(renderer);                  // Affichage
    // SDL_Delay(2000);                              // Pause en ms

    // SDL_RenderClear(renderer);                    // Effacer la fenêtre
}

// void playGirlAnimation(SDL_Texture *sprite,
//                     SDL_Window *window,
//                     SDL_Renderer *renderer)
// {
//     SDL_Rect
//         source = {0},                             // Rectangle définissant la zone de la texture à récupérer
//         window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
//         destination = {0},                        // Rectangle définissant où la zone_source doit être déposée dans le renderer
//         state = {0};

//     SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
//                         &window_dimensions.w, 
//                         &window_dimensions.h); 

//     SDL_QueryTexture(sprite, NULL, NULL,    // Récupération des dimensions de l'image
//                     &source.w, &source.h); 

//     int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
//     float zoom = 0.5;                        // zoom, car ces images sont un peu petites
//     int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
//         offset_y = source.h;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


//     state.x = 0 ;   
//     state.y = 0;                       // La première vignette est en début de ligne
//     //    state.y = 3 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
//     state.w = offset_x;                    // Largeur de la vignette
//     state.h = offset_y;                    // Hauteur de la vignette

//     destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
//     destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

//     destination.y =                        // La course se fait en milieu d'écran (en vertical)
//         (window_dimensions.h - destination.h) * 0.66;

//     int speed = 9;
//     for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
//          destination.x = x;                   // Position en x pour l'affichage du sprite
//          state.x += offset_x;                 // On passe à la vignette suivante dans l'image
//          state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
//                                               // celle de début de ligne
//          SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
//                         &state,
//                         &destination);  
//     }
// }


void playAnimation(SDL_Texture *bg_texture,
                   SDL_Texture *sprite1,
                   SDL_Texture *sprite2,
                   SDL_Window *window,
                   SDL_Renderer *renderer) {
    SDL_Rect
        source1 = {0},   
        source2 = {0},                           // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
        destination1 = {0}, 
        destination2 = {0},                       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state1 = {0},
        state2 = {0};

    SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                        &window_dimensions.w, 
                        &window_dimensions.h); 

    SDL_QueryTexture(sprite1, NULL, NULL,    // Récupération des dimensions de l'image
                    &source1.w, &source1.h); 

    int nb_images_sprite1 = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom1 = 0.5;                        // zoom, car ces images sont un peu petites
    int offset1_x = source1.w / nb_images_sprite1,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset1_y = source1.h;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

    state1.x = 0;   
    state1.y = 0;  
    state1.w = offset1_x;                    // Largeur de la vignette
    state1.h = offset1_y; 
    destination1.w = offset1_x * zoom1;       // Largeur du sprite à l'écran
    destination1.h = offset1_y * zoom1;  
    destination1.y =                        // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination1.h) * 0.66;

    SDL_QueryTexture(sprite2, NULL, NULL,    // Récupération des dimensions de l'image
                    &source2.w, &source2.h); 

    int nb_images_sprite2 = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom2 = 0.55;                        // zoom, car ces images sont un peu petites
    int offset2_x = source2.w / nb_images_sprite2,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset2_y = source2.h; 

    state2.x = 0;   
    state2.y = 0; 
    state2.w = offset2_x;                    // Largeur de la vignette
    state2.h = offset2_y;  

    destination2.w = offset2_x * zoom2;       // Largeur du sprite à l'écran
    destination2.h = offset2_y * zoom2;       // Hauteur du sprite à l'écran
    destination2.y =                        // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination2.h) * 0.675;


    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination2.w + 100; x += speed) {
        
        state1.x += offset1_x;           
        state1.x %= source1.w; 
        destination1.x = x;
                       
        state2.x += offset2_x;
        state2.x %= source2.w;          
        destination2.x = x - 100;  

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        setBackground(bg_texture, window,renderer);
        SDL_RenderCopy(renderer, sprite1, // Préparation de l'affichage
                        &state1,
                        &destination1);  
                        
        SDL_RenderCopy(renderer, sprite2, // Préparation de l'affichage
                        &state2,
                        &destination2);
        
         SDL_RenderPresent(renderer);         // Affichage
         SDL_Delay(80);                       // Pause en ms
    }
    SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
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


    SDL_Texture * background;
    background = loadTextureFromImage("img/sunset-at-pixel-city-8s.jpg", window, renderer);

    SDL_Texture * spriteOfTheGirl;
    spriteOfTheGirl = loadTextureFromImage("img/ramonaflowers.png", window, renderer);

    SDL_Texture * spriteOfTheBoy;
    spriteOfTheBoy = loadTextureFromImage("img/scottpilgrim.png", window, renderer);

    playAnimation(background, spriteOfTheGirl, spriteOfTheBoy, window, renderer);



    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */;
    IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);

    return 0;
}