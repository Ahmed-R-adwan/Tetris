#include "mouseinput.h"
bool MouseInput::CheckMousethere(int& x,int& y,int& w,int& h)
{
    update();
    if( !( x>X || (x+w)<X || y>Y || (y+h)<Y ) )
    {
        return true;
    }
    return false;
}
bool MouseInput::CheckMousethere(SDL_Rect& rech)
{
    update();
    if( !(rech.x>X || (rech.x+rech.w)<X || rech.y>Y || (rech.y+rech.h)<Y)  )
    {
        return true;
    }
    return false;
}
bool MouseInput::CheckMouseMotion(SDL_Event& e,int& x,int& y,int& w,int& h)
{
    if(CheckMousethere(x,y,w,h))
    {
        if(e.type == SDL_MOUSEMOTION)
        {
            return true;
        }
    }
    return false;
}
bool MouseInput::CheckMouseMotion(SDL_Event& e,SDL_Rect& rech)
{
    if(CheckMousethere(rech))
    {
        if(e.type == SDL_MOUSEMOTION)
        {
            return true;
        }
    }
    return false;
}
bool MouseInput::MouseButtonDown(SDL_Event& e,int& x,int& y,int& w,int& h)
{
    if(CheckMousethere(x,y,w,h))
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            return true;
        }
    }
    return false;
}
bool MouseInput::MouseButtonDown(SDL_Event& e,SDL_Rect& rech)
{
    if(CheckMousethere(rech))
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            return true;
        }
    }
    return false;
}
bool MouseInput::MouseButtonUp(SDL_Event& e,int& x,int& y,int& w,int& h)
{
    if(CheckMousethere(x,y,w,h))
    {
        if(e.type == SDL_MOUSEBUTTONUP)
        {
            return true;
        }
    }
    return false;
}
bool MouseInput::MouseButtonUp(SDL_Event& e,SDL_Rect& rech)
{
    if(CheckMousethere(rech))
    {
        if(e.type == SDL_MOUSEBUTTONUP)
        {
            return true;
        }
    }
    return false;
}
void MouseInput::update()
{
    SDL_GetMouseState(&X,&Y);
}
