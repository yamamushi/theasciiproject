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


uint32_t pixels::Get_Pixel( int x, int y, SDL_Surface *surface){

int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }

}

void pixels::Put_Pixel( int x, int y, uint32_t pixel, SDL_Surface *surface){

int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }

} 


SDL_Surface* pixels::SDL_ScaleSurface( SDL_Surface *Surface, Uint16 Width, Uint16 Height){

    if(!Surface || !Width || !Height)
        return 0;
     
    SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel, Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
 
    double _stretch_factor_x = (static_cast<double>(Width)  / static_cast<double>(Surface->w)),
        _stretch_factor_y = (static_cast<double>(Height) / static_cast<double>(Surface->h));
 
    for(Uint32 y = 0; y < Surface->h; y++)
        for(Uint32 x = 0; x < Surface->w; x++)
            for(Uint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(Uint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
                  Put_Pixel32( static_cast<Uint32>(_stretch_factor_x * x) + o_x,  static_cast<Uint32>(_stretch_factor_y * y) + o_y, pixels::Get_Pixel32( x, y, Surface), _ret);
 
    return _ret;


}
