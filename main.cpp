#include "init.h"
#include "game.h"

using namespace std;

int main( int argc, char* args[] )
{
    //random seed
    srand(time(NULL));

    //starting
    SDL_Window* mainWindow = NULL;
    SDL_Renderer* mainRenderer = NULL;

    //initializing
    if(!init(&mainWindow,&mainRenderer))
    {
        printf("Failed to initialize\n");
        return 0;
    }
    else
    {
        game(mainRenderer);
    }

    //"closing
    close(mainWindow,mainRenderer);

    return 0;
}
