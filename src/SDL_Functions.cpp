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
        
    }
    
    return optimizedImage;
    
}



void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    
    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface(source, NULL, destination, &offset);
    
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
    
    SDL_WM_SetCaption("Event Test", NULL);
    
    return true;
    
}




bool load_files()
{
    
    extern SDL_Surface *image;
    image = load_image("../data/images/dispose/x.png");
    
    if(image == NULL)
    {
        return false;
    }
    
    return true;
}




void clean_up()
{
    extern SDL_Surface *image;
    SDL_FreeSurface(image);
    SDL_Quit();    
    
}















