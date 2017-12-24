#include "texture.h"

TTF_Font* Texture::font=NULL;
bool Texture::fontloaded=false;

Texture::Texture()
{
    texture=NULL;
    height=0;
    width=0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile(string path,SDL_Renderer* Render,bool Colorkeying,Uint8 red, Uint8 green, Uint8 blue)
{
    free();
    SDL_Texture* tempTexture=NULL;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if( surface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        if(Colorkeying)
            SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,red,green,blue));
        tempTexture = SDL_CreateTextureFromSurface(Render,surface);
        if(tempTexture==NULL)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            width=surface->w;
            height=surface->h;
        }
        SDL_FreeSurface(surface);
    }

    texture=tempTexture;
    return texture!=NULL;
}

bool Texture::loadFromRenderedText(string textureText,SDL_Color textColor,SDL_Renderer* Render,bool Colorkeying
                                   ,Uint8 red, Uint8 green, Uint8 blue)
{
    free();
    SDL_Texture* tempTexture=NULL;
    if(fontloaded)
    {
        SDL_Surface* surface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
        if( surface == NULL )
        {
            printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        else
        {
            if(Colorkeying)
                SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,red,green,blue));
            tempTexture = SDL_CreateTextureFromSurface(Render,surface);
            if(tempTexture==NULL)
            {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                width=surface->w;
                height=surface->h;
            }
            SDL_FreeSurface(surface);
        }

        texture=tempTexture;
    }
    else
    {
        printf("You need to load a font first");
    }
    return texture!=NULL;
}

void Texture::free()
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture=NULL;
        height=0;
        width=0;
    }
}

void Texture::render(int x,int y,SDL_Renderer* renderer, SDL_Rect* Rect,double angle,SDL_Point* center,SDL_RendererFlip flip)
{
    SDL_Rect rect= {x,y,width,height};
    if(Rect!=NULL)
    {
        rect.w=Rect->w;
        rect.h=Rect->h;
    }
    SDL_RenderCopyEx(renderer,texture,Rect,&rect,angle,center,flip);
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod(texture,red,green,blue);
}

void Texture::setBlindMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(texture,blending);
}

void Texture::setAlphaMod(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(texture,alpha);
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

void Texture::init()
{
//    Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

//    Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
}

void Texture::close()
{
    TTF_CloseFont(font);
    font = NULL;
    fontloaded = false;

    TTF_Quit();
    IMG_Quit();
}

bool Texture::fontload(string path,int Size)
{
    if(fontloaded)
    {
        TTF_CloseFont(font);
        font = NULL;
    }
    font = TTF_OpenFont( path.c_str(), Size );
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        return fontloaded;
    }
    fontloaded=true;
    return fontloaded;
}
