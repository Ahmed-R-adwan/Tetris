#ifndef FPS_H
#define FPS_H

#include <SDL.h>
#include <sstream>
#include <string>

using namespace std;

class FPS
{
    public:
        const int SCREEN_FPS = 60;
        const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
        FPS();
        void startfps();
        void startframecap();
        Uint32 getTicks();
        float getFps(bool integer=false);
        string getFpsAsString(bool integer=false);
        void update(bool cap=false);
        void framecap();
    private:
        unsigned int countedFrames;
        Uint32 startTicks;
        Uint32 frameCap;
};

#endif // FPS_H
