#include "rect.h"

Rect::Rect()
{
    innerRect={2,2,RECT_SIZE-4,RECT_SIZE-4};
    outterRect={0,0,RECT_SIZE,RECT_SIZE};
}

void Rect::render(int x ,int y,SDL_Renderer* mainRenderer,Uint8 red,Uint8 green,Uint8 blue,Uint8 alpha)
{
    innerRect.x=x+2;
    innerRect.y=y+2;
    outterRect.x=x;
    outterRect.y=y;

    SDL_SetRenderDrawColor( mainRenderer,red,green,blue,alpha);
    SDL_RenderFillRect( mainRenderer, &innerRect );
    SDL_RenderDrawRect( mainRenderer, &outterRect );
}
