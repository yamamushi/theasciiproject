//
//  SDL_Functions.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/8/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#pragma once

#ifndef The_ASCII_Project_SDL_Functions_h
#define The_ASCII_Project_SDL_Functions_h

#include "screen_constants.h"

#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
#include "SDL_mixer/SDL_mixer.h"


#include <string>



SDL_Surface *load_image(std::string filename);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
bool init();
bool load_files();
void clean_up();

#endif
