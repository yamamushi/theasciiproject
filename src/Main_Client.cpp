//
//  main.cpp
//  Server
//
//  Created by Jonathan Rumion on 10/7/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//



#include "SDL_Functions.h"


SDL_Surface *background = NULL;


SDL_Surface *message = NULL;

SDL_Surface *upMessage = NULL;
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;

SDL_Surface *screen = NULL;
SDL_Event event;

//SDL_Rect clip[4];
TTF_Font *font = NULL;
SDL_Color textColor = {255, 255, 255};

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
    

    message = TTF_RenderText_Solid( font, "The quick brown fox jumps over the lazy dog", textColor );
    
    upMessage = TTF_RenderText_Solid( font, "Up Pressed", textColor );
    downMessage = TTF_RenderText_Solid( font, "Down Pressed", textColor );
    leftMessage = TTF_RenderText_Solid( font, "Left Pressed", textColor );
    rightMessage = TTF_RenderText_Solid( font, "Right Pressed", textColor );
    


    
    while(quit == false)
    {
        
        while(SDL_PollEvent(&event))
        {
            
            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: message = upMessage; break;
                    case SDLK_DOWN: message = downMessage; break;
                    case SDLK_LEFT: message = leftMessage; break;
                    case SDLK_RIGHT: message = rightMessage; break;
                    case SDLK_ESCAPE: quit = true; break;
                    default: ;
                        
                }
            }
            
            
            else if(event.type == SDL_QUIT)
            {
                quit = true;
            }
 
        }
        
        if(message != NULL)
        {
            apply_surface(0,0,background,screen);
            apply_surface((SCREEN_WIDTH - message->w) / 2, (SCREEN_HEIGHT - message->h) / 2, message, screen);
            
            message = NULL;
        }
        
        if(SDL_Flip(screen) == -1)
        {
            return 1;
        }
        
        
    }

    clean_up();
    
    return 0;
    
}

