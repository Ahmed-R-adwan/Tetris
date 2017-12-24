#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <SDL.h>

class MouseInput
{
public:
    bool CheckMousethere(int& x,int& y,int& w,int& h);
    bool CheckMousethere(SDL_Rect& rech);

    bool CheckMouseMotion(SDL_Event& ,int& x,int& y,int& w,int& h);
    bool CheckMouseMotion(SDL_Event& ,SDL_Rect& rech);

    bool MouseButtonDown(SDL_Event& ,int& x,int& y,int& w,int& h);
    bool MouseButtonDown(SDL_Event& ,SDL_Rect& rech);

    bool MouseButtonUp(SDL_Event& ,int& x,int& y,int& w,int& h);
    bool MouseButtonUp(SDL_Event& ,SDL_Rect& rech);

    void update();
private:
    int X,Y;
};

#endif // MOUSEINPUT_H
