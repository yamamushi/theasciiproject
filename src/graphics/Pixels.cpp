/*
  
  Pixels 
  A set of functions for working with individual Pixels
  -Yamamushi (Jon Rumion)
  2012 - 12 - 12

 */

#include "Pixels.h"
#include "SDL/SDL.h"


uint32_t pixels::Get_Pixel32( int x, int y, SDL_Surface *surface){

//Convert the pixels to 32 bit
  uint32_t *pixels = (uint32_t *)surface->pixels;

//Get the pixel requested
  return pixels[ ( y * surface->w ) + x ];

}


void pixels::Put_Pixel32( int x, int y, uint32_t pixel, SDL_Surface *surface){

  uint32_t *pixels = (uint32_t *)surface->pixels;
  
  pixels[ ( y * surface->w ) + x ] = pixel;


}
