/*

  BitmapFont Class functions
  -Yamamushi

 */



#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "BitmapFont.h"

#include <string>
BitmapFont::BitmapFont(){

}


BitmapFont::BitmapFont( SDL_Surface *surface){


}


void BitmapFont::Build_Font( SDL_Surface *surface){


}


void BitmapFont::Show_Text( int x, int y, std::string source, SDL_Surface *surface){


}



uint32_t BitmapFont::Get_Pixel32( int x, int y, SDL_Surface *surface){

//Convert the pixels to 32 bit
 uint32_t *pixels = (uint32_t *)surface->pixels;

//Get the pixel requested
 return pixels[ ( y * surface->w ) + x ];

}

