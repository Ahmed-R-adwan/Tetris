#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <utility>
#include <string.h>
#include <math.h>
#include <algorithm>

#include "rect.h"
#include "Defines.h"

using namespace std;

class Object
{
    public:
        Object(int Type);
        void render(SDL_Renderer* mainRenderer);
        void update(bool** gameRects);
        void reset(int Type);
        void saverects(bool** gameRects);
        void event(SDL_Event e,bool** gameRects);
        void Rotate(bool** gameRects);
        bool overlap(bool** gameRects);
        bool overlap(bool** gameRects,pair<int,int> testobject[4][4]);

        int x,y;
        bool dead;
    private:
        Uint8 red=0;
        Uint8 green=0;
        Uint8 blue=255;
        Uint8 alpha=0;

        bool keydown=0;
        int type,height,width;
        Rect rect;
        pair<int,int> object[4][4];
};

#endif // OBJECT_H
