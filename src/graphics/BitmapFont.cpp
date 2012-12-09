/*

  BitmapFont Class functions
  -Yamamushi

  Adapted from http://lazyfoo.net/SDL_tutorials/lesson30/index.php

 */

#include "BitmapFont.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <string>



BitmapFont::BitmapFont(){

     bitmap = nullptr;
     newLine = 0;
     space = 0;

}


BitmapFont::BitmapFont( SDL_Surface *surface){

     Build_Font( surface );

}


void BitmapFont::Build_Font( SDL_Surface *surface){

     if( surface == nullptr){
          return;
     }

     // Load our bitmap font
     bitmap = surface;
     uint32_t bgColor = SDL_MapRGB( bitmap->format, 0, 0xFF, 0xFF );

     // Character Cell dimensions
     int cellW = bitmap->w / 32;
     int cellH = bitmap->h / 2048;

     // New Line Variables
     int top = cellH;
     int baseA = cellH;

     // The current chars[%] value we're setting
     int currentChar = 0;

     // Start by cell rows
     for( int rows = 0; rows < 32; rows++){
       for( int cols = 0; cols < 2048; cols++){
         // Start by setting our Character offsets
         chars[currentChar]->x = cellW * cols;

       }
     }

}


void BitmapFont::Show_Text( int x, int y, std::string source, SDL_Surface *surface){


}



uint32_t BitmapFont::Get_Pixel32( int x, int y, SDL_Surface *surface){

//Convert the pixels to 32 bit
     uint32_t *pixels = (uint32_t *)surface->pixels;

//Get the pixel requested
     return pixels[ ( y * surface->w ) + x ];

}

