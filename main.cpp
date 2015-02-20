#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"�chec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    IMG_Init(IMG_INIT_JPG);

    /* Cr�ation de la fen�tre */
    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Ma premi�re application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                              SDL_WINDOWPOS_UNDEFINED,
                                                              640,
                                                              480,
                                                              SDL_WINDOW_SHOWN);


    SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Cr�ation d'un SDL_Renderer utilisant l'acc�l�ration mat�rielle
    if ( pRenderer )
    {
        //SDL_Surface* pSprite = SDL_LoadBMP("allo.bmp");
        SDL_Surface *pSprite = IMG_Load ( "allo.png" );
        if ( pSprite )
        {
            SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite); // Pr�paration du sprite
            if ( pTexture )
            {
                SDL_Rect dest = { 640/2 - pSprite->w/2,480/2 - pSprite->h/2, pSprite->w, pSprite->h};
                SDL_RenderCopy(pRenderer,pTexture,NULL,&dest); // Copie du sprite gr�ce au SDL_Renderer

                SDL_RenderPresent(pRenderer); // Affichage
                SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fen�tre */

                SDL_DestroyTexture(pTexture); // Lib�ration de la m�moire associ�e � la texture
            }
            else
            {
                fprintf(stdout,"�chec de cr�ation de la texture (%s)\n",SDL_GetError());
            }

            SDL_FreeSurface(pSprite); // Lib�ration de la ressource occup�e par le sprite
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
