#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <SDL.h>
#include <stdio.h>
#include <vector>

#include "texture.h"
#include "Defines.h"

bool init(SDL_Window* window);
void close(SDL_Window* window);

bool init(SDL_Window** window,SDL_Renderer** renderer)
{
    bool success=true;

    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        success=false;
    }
    else
    {
        *window=SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success=false;
        }
        else
        {

            Texture::init();

            //Renderer creation
            *renderer=SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success=false;
            }

        }
    }

    return success;
}

void close(SDL_Window* window,SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer=NULL;
    Texture::close();
    SDL_Quit();
}

#endif // INIT_H
