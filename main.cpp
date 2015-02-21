#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Cat.h>
#include <Timer.h>
#include <Const.h>

#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    //IMG_Init(IMG_INIT_JPG);

    //Les surfaces

    SDL_Rect dest;
    SDL_Rect source;

    //La structure d'événements que nous allons utiliser
    SDL_Event event;

    //Les zones de la feuille de sprite
    SDL_Rect clipsRight[3];
    SDL_Rect clipsLeft[3];

    for(int i=0;i<3;i++) {
        clipsRight[ i ].x = CAT_WIDTH * i;
        clipsRight[ i ].y = 0;
        clipsRight[ i ].w = CAT_WIDTH;
        clipsRight[ i ].h = CAT_HEIGHT;

        clipsLeft[ i ].x = CAT_WIDTH * i;
        clipsLeft[ i ].y = CAT_HEIGHT;
        clipsLeft[ i ].w = CAT_WIDTH;
        clipsLeft[ i ].h = CAT_HEIGHT;
    }

    bool quit = false;
    Cat cat;
    Timer fps;

    const Uint8 *state = SDL_GetKeyboardState(NULL);


    /* Création de la fenêtre */
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                              SDL_WINDOWPOS_UNDEFINED,
                                                              SCREEN_WIDTH,
                                                              SCREEN_HEIGHT,
                                                              SDL_WINDOW_SHOWN);

    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,0); // Création d'un SDL_Renderer utilisant l'accélération matérielle
    if ( pRenderer )
    {
        //SDL_Surface* pSprite = SDL_LoadBMP("allo.bmp");
        SDL_Surface *pSprite = IMG_Load ( "cat.png" );
        SDL_Surface *screen  = IMG_Load ( "background.png" );
        Uint32 colorkey = SDL_MapRGB( pSprite->format, 0, 255, 255);
        SDL_SetColorKey(pSprite, SDL_TRUE,colorkey);
        if ( pSprite )
        {
            SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Préparation du sprite
            SDL_Texture* background = SDL_CreateTextureFromSurface(pRenderer,screen); // Préparation du sprite
                fps.start();
                int continuerNewGame = 1;
                while(continuerNewGame){


                    SDL_PollEvent(&event);
                    //SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
                    //SDL_RenderClear(pRenderer);
                    //SDL_RenderClear(pRenderer);

                    //SDL_RenderCopy(pRenderer,pTexture,&source,&dest); // Copie du sprite grâce au SDL_Renderer
                    //SDL_RenderPresent(pRenderer); // Affichage

                    //cat.handle_events(event);

                    switch(event.type){
                        case SDL_QUIT:
                            continuerNewGame = 0;
                            break;
                        case SDL_KEYDOWN:
                            break;
                    }

                    //if(state[SDL_SCANCODE_LEFT]) {posx -= 5;}
                    //if(state[SDL_SCANCODE_RIGHT]) {posx += 5;}
                    //if(state[SDL_SCANCODE_UP]) {posy -= 5;}
                    //if(state[SDL_SCANCODE_DOWN]) {posy += 5;}
                    //if(state[SDL_SCANCODE_Q]) {posx2 -= 5;}
                    //if(state[SDL_SCANCODE_D]) {posx2 += 5;}
                    //if(state[SDL_SCANCODE_Z]) {posy2 -= 5;}
                    //if(state[SDL_SCANCODE_S]) {posy2 += 5;}



                    if(state[SDL_SCANCODE_RIGHT])
                    {
                        cat.updateVelocity(CONST_VEL_INC);
                    }

                    if(state[SDL_SCANCODE_LEFT]){
                        cat.updateVelocity(-CONST_VEL_INC);
                    }
                    if (!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
                    {cat.updateVelocity(0);}

                    cat.updateAnim();

                    if (fps.get_ticks() > 1000 / FRAMES_PER_SECOND){
                        cat.updateFrame();
                        fps.reset();
                    }

                    if( cat.getStatus() == CAT_RIGHT ){
                        source = clipsRight[cat.getFrame()];
                        //apply_surface( cat.getOffSet(), SCREEN_HEIGHT - CAT_HEIGHT, cat, screen, &clipsRight[ cat.getFrame() ] );
                    }
                    else if( cat.getStatus() == CAT_LEFT ){
                        source = clipsLeft[cat.getFrame()];
                        //apply_surface( cat.getOffSet(), SCREEN_HEIGHT - CAT_HEIGHT, cat, screen, &clipsLeft[ cat.getFrame() ] );
                    }

                    dest = { CONST_POSX_INI + cat.getOffset() - pSprite->w/2, CONST_POSY_INI - pSprite->h/2, CAT_WIDTH, CAT_HEIGHT};
                    SDL_RenderCopy(pRenderer,background,NULL,NULL); // Copie du sprite grâce au SDL_Renderer
                    SDL_RenderCopy(pRenderer,pTexture,&source,&dest); // Copie du sprite grâce au SDL_Renderer


                    //fprintf(stdout,"Velocity (%s)\n",cat.getVelocity());
                    //fprintf(stdout,"Offset (%s)\n",cat.getOffset());
                    cout << "velocity: " << cat.getVelocity() << endl;

                    SDL_RenderPresent(pRenderer); // Affichage
                    SDL_Delay(10);
                }

                SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

            SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
        }
        else
        {
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

        SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer
    }
    else
    {
        fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
    }

    SDL_Quit();

    return 0;
}
