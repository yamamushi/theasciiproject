//
//  main.cpp
//  Server
//
//  Created by Jonathan Rumion on 10/7/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//



#include "SDL_Functions.h"


SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;
SDL_Event event;


int main( int argc, char* args[] )
{
    
    bool quit = false;
    
    if(init() == false)
    {
        return 1;
    }
    
    if(load_files() == false)
    {
        return 1;
    }
    
    apply_surface(0, 0, image, screen);
    
    if(SDL_Flip(screen) == -1)
    {
        return 1;
    }
    
    while(quit == false)
    {
        
        while(SDL_PollEvent(&event))
        {
            
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            
            
        }
        
        
        
    }

    clean_up();
    
    return 0;
    
}

