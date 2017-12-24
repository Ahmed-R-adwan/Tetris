#include "object.h"

Object::Object(int Type)
{
    reset(Type);
}

void Object::render(SDL_Renderer* mainRenderer)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(object[i][j].first!=-1)
            {
                rect.render(object[i][j].first+x,object[i][j].second+y,mainRenderer,red,green,blue,alpha);
            }
        }
    }
}

void Object::reset(int Type)
{
    dead=0;
    type=Type;
    y=0;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            object[i][j]= {-1,-1};
        }
    }

    x=START_POSITION;

    if(type==IBLOCK)
    {
        height=4;
        width=1;
        object[0][2]= {0,0};
        object[1][2]= {0,RECT_SIZE};
        object[2][2]= {0,RECT_SIZE*2};
        object[3][2]= {0,RECT_SIZE*3};
    }
    else if(type==RIGHTL)
    {
        height=3;
        width=2;
        object[0][2]= {0,0};
        object[1][2]= {0,RECT_SIZE};
        object[2][2]= {0,RECT_SIZE*2};
        object[2][3]= {RECT_SIZE,RECT_SIZE*2};
    }
    else if(type==LEFTL)
    {
        height=3;
        width=2;
        object[0][2]= {RECT_SIZE,0};
        object[1][2]= {RECT_SIZE,RECT_SIZE};
        object[2][2]= {RECT_SIZE,RECT_SIZE*2};
        object[2][1]= {0,RECT_SIZE*2};
    }
    else if(type==NORMAL_BLOCK)
    {
        height=2;
        width=2;
        object[1][1]= {0,0};
        object[1][2]= {0,RECT_SIZE};
        object[2][1]= {RECT_SIZE,0};
        object[2][2]= {RECT_SIZE,RECT_SIZE};
    }
    else if(type==TBLOCK)
    {
        height=2;
        width=3;
        object[0][1]= {0,0};
        object[0][2]= {RECT_SIZE,0};
        object[0][3]= {RECT_SIZE*2,0};
        object[1][2]= {RECT_SIZE,RECT_SIZE};
    }
    else if(type==ZBLOCK)
    {
        height=2;
        width=3;
        object[0][2]= {0,0};
        object[0][3]= {RECT_SIZE,0};
        object[1][2]= {RECT_SIZE,RECT_SIZE};
        object[1][3]= {RECT_SIZE*2,RECT_SIZE};
    }
    else if(type==SBLOCK)
    {
        height=2;
        width=3;
        object[1][2]= {RECT_SIZE,0};
        object[1][3]= {RECT_SIZE*2,0};
        object[2][2]= {RECT_SIZE,RECT_SIZE};
        object[2][3]= {0,RECT_SIZE};
    }
}

bool Object::overlap(bool** gameRects)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(object[i][j].first!=-1)
            {
                if(gameRects[ ( (object[i][j].first+x) /RECT_SIZE)][( (object[i][j].second+y) /RECT_SIZE)]==1)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void Object::update(bool** gameRects)
{
    y+=SPEED;
    if((y+RECT_SIZE*height)>GAME_HEIGHT )
    {
        y-=SPEED;
        dead=1;
        return ;
    }
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(object[i][j].first!=-1)
            {
                if(gameRects[ ( (object[i][j].first+x) /RECT_SIZE)][( (object[i][j].second+y) /RECT_SIZE)]==1)
                {
                    y-=SPEED;
                    dead=1;
                    return ;
                }
            }
        }
    }
}

void Object::saverects(bool** gameRects)
{
    dead=0;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(object[i][j].first!=-1)
            {
                gameRects[ ( (object[i][j].first+x) /RECT_SIZE)][( (object[i][j].second+y) /RECT_SIZE)]=1;
            }
        }
    }
}

void Object::event(SDL_Event e,bool** gameRects)
{
    int Move=0;
    if(e.type == SDL_KEYUP)
        switch( e.key.keysym.sym )
        {
        case SDLK_LEFT:
            keydown=0;
            break;
        case SDLK_RIGHT:
            keydown=0;
            break;
        case SDLK_SPACE:
            keydown=0;
            break;
        }

    if(e.type == SDL_KEYDOWN)
        switch( e.key.keysym.sym )
        {
        case SDLK_LEFT:
            keydown=1;
            Move = -SPEED;
            x+=Move;
            break;
        case SDLK_RIGHT:
            keydown=1;
            Move = +SPEED;
            x+=Move;
            break;
        case SDLK_SPACE:
            Rotate(gameRects);
            keydown=1;
            break;
        }

    if( ( ( x+(RECT_SIZE*width) ) > GAME_WIDTH ) || x<0 )
    {
        x-=Move;
        return ;
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(object[i][j].first!=-1)
            {
                if(gameRects[ ( (object[i][j].first+x) /RECT_SIZE)][( (object[i][j].second+y) /RECT_SIZE)]==1)
                {
                    x-=Move;
                    return ;
                }
            }
        }
    }

}

void  Object::Rotate(bool** gameRects)
{
    pair<int,int> box;
    pair<int,int> testobject[4][4],Max = {INT_MIN,INT_MIN} , Min= {INT_MAX,INT_MAX};

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            testobject[i][j]={-1,-1};
            if(object[i][j].first!=-1)
            {
                box.first= -object[i][j].second;
                box.second= object[i][j].first;
                testobject[i][j]=box;
                Max.first=max(Max.first,testobject[i][j].first);
                Max.second=max(Max.second,testobject[i][j].second);
                Min.first=min(Min.first,testobject[i][j].first);
                Min.second=min(Min.second,testobject[i][j].second);
            }
        }
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(testobject[i][j].first!=-1)
            {
                if( Min.first<x )
                {
                    testobject[i][j].first-=Min.first;
                    Max.first=max(Max.first,testobject[i][j].first);
                }
                if( Min.second<y )
                {
                    testobject[i][j].second-=Min.second;
                    Max.second=max(Max.second,testobject[i][j].second);
                }
            }
        }
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(testobject[i][j].first!=-1)
            {
                if( Max.first+x+RECT_SIZE>GAME_WIDTH )
                {
                    x+=(GAME_WIDTH - (Max.first+x+RECT_SIZE) );
                }
                if( Max.second+y+RECT_SIZE>GAME_HEIGHT )
                {
                    y+=(GAME_HEIGHT - (Max.second+y+RECT_SIZE) );
                }
            }
        }
    }

    if(overlap(gameRects,testobject)){return ;}

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            object[i][j]=testobject[i][j];
        }
    }
    swap(width,height);
}

bool Object::overlap(bool** gameRects,pair<int,int> testobject[4][4])
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(testobject[i][j].first!=-1)
            {
                if(gameRects[ ( (testobject[i][j].first+x) /RECT_SIZE)][( (testobject[i][j].second+y) /RECT_SIZE)]==1)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
