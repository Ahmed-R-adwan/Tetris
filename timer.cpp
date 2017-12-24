#include "timer.h"

Timer::Timer()
{
    startTicks=0;
    pauseTicks=0;
    startState=false;
    pauseState=false;
}

void Timer::start()
{
    startState=true;
    pauseState=false;
    startTicks=SDL_GetTicks();
    pauseTicks=0;
}

void Timer::stop()
{

    startState=false;
    pauseState=false;
    startTicks=0;
    pauseTicks=0;
}

void Timer::pause()
{
    if( startState && !pauseState )
    {
        pauseState = true;
        pauseTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if( startState && pauseState )
    {
        pauseState = false;
        startTicks = SDL_GetTicks() - pauseTicks;
        pauseTicks = 0;
    }
}

Uint32 Timer::getTicks()
{
    Uint32 time = 0;

    if( startState )
    {
        if( pauseState )
        {
            time = pauseTicks;
        }
        else
        {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}

string Timer::getTicksAsString()
{
    Uint32 time = getTicks();
    stringstream sTime;
    sTime<<time;
    return sTime.str();
}

bool Timer::isstarted()
{
    return startState;
}

bool Timer::ispaused()
{
    return pauseState&&startState;
}
