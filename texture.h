#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class Texture
{
    public:
        Texture();
        ~Texture();
        bool loadFromFile(string,SDL_Renderer*,bool =false ,Uint8=0,Uint8=0,Uint8=0);
        bool loadFromRenderedText(string textureText, SDL_Color textColor,SDL_Renderer*,bool =false ,Uint8=0,Uint8=0,Uint8=0);
        void free();
        void render(int,int,SDL_Renderer*, SDL_Rect* =NULL,double =0.0,SDL_Point* =NULL,SDL_RendererFlip =SDL_FLIP_NONE);
        void setColor(Uint8,Uint8,Uint8);
        void setBlindMode(SDL_BlendMode);
        void setAlphaMod(Uint8);
        int getWidth();
        int getHeight();
        static void init();
        static void close();
        static bool fontload(string,int);
    private:
        SDL_Texture* texture;
        int width;
        int height;
        static TTF_Font* font;
        static bool fontloaded;
};
#endif // TEXTURE_H
