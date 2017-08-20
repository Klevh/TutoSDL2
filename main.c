/*include des headers standards en C*/
#include <stdio.h>

/*include des headers definies par le programmeur (moi, toi, vous, nous ...)
 * il contient les includes pour la SDL2
 */
#include "moteur.h"

/* fonction d'affichage de la fenetre */
void display(data_t data);

/* fonction principale */
int main(){
    /* variable d'initialisation de SDL_image */
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    /* variable liee a la fenetre */
    SDL_Window * window;
    /* variables liees a la capture d'evenement */
    SDL_Event event;
    int run = 1;
    /* paquet d'informations : l'image, le texte et le rectangle ainsi que leur positions */
    data_t data;

    /* initialisation de la SDL2 */
    if(SDL_Init(SDL_INIT_VIDEO) == 1){
        fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        return EXIT_FAILURE;
    }
    
    /* initialisation de SDL_ttf */
    if (TTF_Init() != 0){
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /* initialisation de SDL_image */
    if((IMG_Init(flags)&flags) != flags){
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /* ouverture de la fenetre */
    window = SDL_CreateWindow("PIXEL : un petit test en SDL2",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              450,450,
                              0); /* ici, c'est l'option d'ouverture (plein ecran, redimensionnable, ...) */
    if(!window){
        fprintf(stderr,"Erreur de creation de la fenetre : %s\n", SDL_GetError());
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /* initialisation du paquet de données */
    data = init_data(window,"arial.ttf","PIXEL", "pixel.png");
    if(!data.img){
        fprintf(stderr,"Erreur d'initialisation des informations complementaires : %s\n",SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    /* boucle d'evenement */
    while(run){
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x < 100 && event.button.y < 40 && event.button.x > 0 && event.button.y > 0)
                    printf("PIXEL\n");
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                case 'z':
                    if((data.pos_img.x >= 100 && data.pos_img.y) || (data.pos_img.y > 40))
                        data.pos_img.y-=4;
                    break;
                case 's':
                    if(data.pos_img.y < 400)
                        data.pos_img.y+=4;
                    break;
                case 'q':
                    if((data.pos_img.x && data.pos_img.y >= 40) || data.pos_img.x > 100)
                        data.pos_img.x-=4;
                    break;
                case 'd':
                    if(data.pos_img.x < 400)
                        data.pos_img.x+=4;
                    break;
                }
                break;
            case SDL_QUIT:
                run = 0;
                break;
            }
        }
        display(data);
        SDL_Delay(1);
    }
    
    /* on libere le paquet d'information */
    close_data(data);
    /* on libere la fenetre */
    SDL_DestroyWindow(window);
    /* fermeture de SDL_image, SDL_ttf et SDL2 */
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}



void display(data_t data){
    SDL_Rect rect;
    
    /* couleur de fond */
    SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 0);
    SDL_RenderClear(data.renderer);

    /* carre blanc en haut a gauche */
    SDL_SetRenderDrawColor(data.renderer, 255, 255, 255, 0);
    rect.x = rect.y = 0;
    rect.w = 100;
    rect.h = 40;
    SDL_RenderFillRect(data.renderer, &rect );

    /* texte en haut a gauche */
    rect.x = rect.y = 10;
    rect.w = 80;
    rect.h = 20;
    SDL_RenderCopy(data.renderer,data.txt,NULL,&rect);

    /* logo pixel en mouvement */
    SDL_RenderCopy(data.renderer,data.img,NULL,&(data.pos_img));

    /* finalisation de l'affichage */
    SDL_RenderPresent(data.renderer);
}
