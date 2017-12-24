#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <sstream>
#include <string>

using namespace std;

class Timer
{
    public:
        Timer();
        void start();
        void stop();
        void pause();
        void unpause();

        Uint32 getTicks();
        string getTicksAsString();

        bool isstarted();
        bool ispaused();
    private:
        Uint32 startTicks;
        Uint32 pauseTicks;
        bool startState;
        bool pauseState;
};
#endif // TIMER_H
