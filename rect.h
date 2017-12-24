#ifndef RECT_H
#define RECT_H

#include <SDL.h>
#include "Defines.h"

class Rect
{
    public:
        Rect();
        void render(int x ,int y,SDL_Renderer* mainRenderer,Uint8 red,Uint8 green,Uint8 blue,Uint8 alpha);
    private:
        SDL_Rect innerRect,outterRect;
};

#endif // RECT_H
