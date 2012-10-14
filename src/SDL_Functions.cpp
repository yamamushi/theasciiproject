//
//  SDL_Functions.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/8/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#include "SDL_Functions.h"




SDL_Surface *load_image(std::string filename)
{
    
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    
    
    loadedImage = IMG_Load(filename.c_str());
    
    if(loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        
        if(optimizedImage != NULL)
        {
            
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
            
        }
        
    }
    
    return optimizedImage;
    
}



void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    
    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface(source, clip, destination, &offset);
    
}



bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
        
    }
    
    extern SDL_Surface *screen;
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    
    if(screen == NULL)
    {
        return false;
    }
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "TTF Test", NULL );
    
    return true;
    
}




bool load_files()
{
    
    extern SDL_Surface *background;
    extern TTF_Font *font;
    
    background = load_image("../data/images/dispose/background.png");
    font = TTF_OpenFont( "../data/fonts/lazy.ttf", 16 );

    
    if(background == NULL || font == NULL)
    {
        return false;
    }
    
    return true;
}




void clean_up()
{
    extern SDL_Surface *message;
    extern SDL_Surface *upMessage;
    extern SDL_Surface *downMessage;
    extern SDL_Surface *leftMessage;
    extern SDL_Surface *rightMessage;
    extern SDL_Surface *background;
    SDL_FreeSurface(message);
    SDL_FreeSurface(upMessage);
    SDL_FreeSurface(downMessage);
    SDL_FreeSurface(leftMessage);
    SDL_FreeSurface(rightMessage);
    SDL_FreeSurface(background);
    SDL_Quit();    
    
}















