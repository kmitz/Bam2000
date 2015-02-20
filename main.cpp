#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
//
using namespace std;

int main(int argc, char** argv)
{

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    //IMG_Init(IMG_INIT_JPG);

    SDL_Event event;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    /* Cr�ation de la fen�tre */
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Ma premi�re application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                              SDL_WINDOWPOS_UNDEFINED,
                                                              640,
                                                              480,
                                                              SDL_WINDOW_SHOWN);
    int posx = 300;
    int posy = 200;
    int posx2 = 300;
    int posy2 = 200;

    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Cr�ation d'un SDL_Renderer utilisant l'acc�l�ration mat�rielle
    if ( pRenderer )
    {
        //SDL_Surface* pSprite = SDL_LoadBMP("allo.bmp");
        SDL_Surface *pSprite = IMG_Load ( "allo.bmp" );
        SDL_Surface *pSprite2 = IMG_Load ( "allo.jpg" );
        if ( pSprite )
        {
            SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Pr�paration du sprite
            SDL_Texture* pTexture2 = SDL_CreateTextureFromSurface(pRenderer,pSprite2); // Pr�paration du sprite

                int continuerNewGame = 1;
                while(continuerNewGame){

                    SDL_PollEvent(&event);
                    SDL_RenderClear(pRenderer);


                    switch(event.type){
                        case SDL_QUIT:
                            continuerNewGame = 0;
                            break;
                        case SDL_KEYDOWN:

                            break;

                    }

                    if(state[SDL_SCANCODE_LEFT]) {posx -= 5;}
                    if(state[SDL_SCANCODE_RIGHT]) {posx += 5;}
                    if(state[SDL_SCANCODE_UP]) {posy -= 5;}
                    if(state[SDL_SCANCODE_DOWN]) {posy += 5;}
                    if(state[SDL_SCANCODE_Q]) {posx2 -= 5;}
                    if(state[SDL_SCANCODE_D]) {posx2 += 5;}
                    if(state[SDL_SCANCODE_Z]) {posy2 -= 5;}
                    if(state[SDL_SCANCODE_S]) {posy2 += 5;}


                    SDL_Rect dest = { posx - pSprite->w/2,posy - pSprite->h/2, pSprite->w, pSprite->h};
                    SDL_Rect dest2 = { posx2 - pSprite->w/2,posy2 - pSprite2->h/2, pSprite2->w, pSprite2->h};
                    SDL_RenderCopy(pRenderer,pTexture,NULL,&dest); // Copie du sprite gr�ce au SDL_Renderer
                    SDL_RenderCopy(pRenderer,pTexture2,NULL,&dest2); // Copie du sprite gr�ce au SDL_Renderer
                    SDL_RenderPresent(pRenderer); // Affichage
                    SDL_Delay(20);
                }

                SDL_DestroyTexture(pTexture); // Lib�ration de la m�moire associ�e � la texture
                SDL_DestroyTexture(pTexture2); // Lib�ration de la m�moire associ�e � la texture



            SDL_FreeSurface(pSprite); // Lib�ration de la ressource occup�e par le sprite
            SDL_FreeSurface(pSprite2); // Lib�ration de la ressource occup�e par le sprite
        }
        else
        {
            fprintf(stdout,"�chec de chargement du sprite (%s)\n",SDL_GetError());
        }

        SDL_DestroyRenderer(pRenderer); // Lib�ration de la m�moire du SDL_Renderer
    }
    else
    {
        fprintf(stdout,"�chec de cr�ation du renderer (%s)\n",SDL_GetError());
    }

    SDL_Quit();

    return 0;
}
