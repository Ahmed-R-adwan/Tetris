#include "fps.h"

FPS::FPS()
{
    countedFrames=0;
    frameCap=0;
}

Uint32 FPS::getTicks()
{
    return SDL_GetTicks() - startTicks;
}

float FPS::getFps(bool integer)
{
    float avgfps = countedFrames / ( getTicks() / 1000.f );
    if( avgfps > 2000000 )
    {
        avgfps = 0;
    }
    if(integer)return ((int)avgfps);
    return avgfps;
}

string FPS::getFpsAsString(bool integer)
{
    stringstream sAvgFps;
    sAvgFps<<getFps(integer);
    return sAvgFps.str();
}

void FPS::update(bool cap)
{
    countedFrames++;
    if(cap)framecap();
}

void FPS::startfps()
{
    startTicks=SDL_GetTicks();
}

void FPS::startframecap()
{
    frameCap=SDL_GetTicks();
}

void FPS::framecap()
{
    int frameTicks = SDL_GetTicks()-frameCap;
    if( frameTicks < SCREEN_TICKS_PER_FRAME )
    {
        SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
    }

}
