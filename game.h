#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <random>
#include"conio.h"

#include "Defines.h"
#include "timer.h"
#include "fps.h"
#include "object.h"

void game(SDL_Renderer* mainRenderer);
void check(bool** object,int& scoure);
void reset(int& SpeedDifficulty,bool** object,bool& ok);

void game(SDL_Renderer* mainRenderer)
{
    Timer time;
    FPS fps;
    SDL_Event e;
    Texture::fontload("arial.ttf",28);
    Texture texture;
    SDL_Color black= {0,0,0,255};
    Uint8 red=0;
    Uint8 green=0;
    Uint8 blue=255;
    Uint8 alpha=0;

    bool** object,quit=0,ok=1;
    int scoure=0,Rand=rand()%7;
    string g="GameOver";

    object = new bool *[10];
    for(int i = 0; i <10; i++)
        object[i] = new bool[20];
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<20; j++)
        {
            object[i][j]=0;
        }
    }

    int SpeedDifficulty=START_DIFFICULTY;

    Object rect(Rand);

    time.start();
    fps.startfps();
    while(!quit)
    {
        if(rect.dead)
        {
            Rand=rand()%7;
            rect.saverects(object);
            rect.reset(Rand);
            if(rect.overlap(object))ok=0;
        }
        check(object,scoure);

        fps.startframecap();
        while(SDL_PollEvent(&e) != 0)
        {
            if( SDL_QUIT == e.type )
            {
                quit=true;
            }
            if(ok)
            {
                rect.event(e,object);
            }
            if(e.key.keysym.sym==SDLK_SPACE && !ok)
            {
                reset(SpeedDifficulty,object,ok);
            }
    }
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    SDL_RenderClear(mainRenderer);

    stringstream ss;
    string s;
    ss<<scoure;
    ss>>s;
    ss.clear();
    texture.loadFromRenderedText(s,black,mainRenderer);
    texture.setAlphaMod(50);
    texture.render(0,0,mainRenderer);

    if(ok)rect.render(mainRenderer);

    if((time.getTicks()/100)%SpeedDifficulty==0 && time.getTicks()>100 && ok)
        {
            rect.update(object);
            time.stop();
            time.start();
        }

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<20; j++)
        {
            Rect R;
            if(object[i][j]==1)
            {
                R.render(RECT_SIZE*i,RECT_SIZE*j,mainRenderer,red,green,blue,alpha);
            }
        }
    }

    if(!ok)
    {
        texture.loadFromRenderedText(g,black,mainRenderer);
        texture.setAlphaMod(100);
        texture.render(0,GAME_HEIGHT/2,mainRenderer);
    }

    //Update screen
    SDL_RenderPresent(mainRenderer);

    fps.update(true);
}

for(int i = 0; i < 10; ++i)
{
    delete [] object[i];
    object[i]=0;
}
delete [] object;
object=0;
}

void check(bool** object,int& scoure)
{
    int c=0;
    for(int i=0; i<20; i++)
    {
        bool ok=1;
        for(int j=0; j<10; j++)
        {
            if(!object[j][i])ok=0;
        }
        if(ok)
        {
            c++;
            scoure+=10;
            for(int j=0; j<10; j++)
            {
                object[j][i]=0;
            }
        }
    }
    for(; c>0; c--)
    {
        for(int i=19; i>0; i--)
        {
            for(int j=0; j<10; j++)
            {
                if(!object[j][i])
                {
                    object[j][i]=object[j][i-1];
                    object[j][i-1]=0;
                }
            }
        }
    }
}

void reset(int& SpeedDifficulty,bool** object,bool& ok)
{
    SpeedDifficulty=START_DIFFICULTY;
    ok=1;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<20; j++)
        {
            object[i][j]=0;
        }
    }
}

#endif // GAME_H
