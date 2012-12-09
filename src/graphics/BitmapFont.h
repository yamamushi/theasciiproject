#pragma once
/*

  BitmapFont Class - Used for generating our font "sprite sheet".

  Note:: This will ONLY work with a full Unicode font (65,535
  characters).

  The font supplied with with the project (font.png) was generated for
  use with this loader.

  -Yamamushi (Jon Rumion)
  12-09-12

 */

#include <string>
#include "SDL/SDL.h"

#if defined __UINT32_MAX__ or UINT32_MAX
#include <inttypes.h>
#else
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
#endif




class BitmapFont {

 private:

  // Our font surface, aka this will point to font.png 
  SDL_Surface *bitmap;
  // All Unicode Characters in the font accounted for
  SDL_Rect *chars[65536];
  
  int newLine, space;


 public:

  BitmapFont();
  BitmapFont( SDL_Surface *surface);

  void Build_Font( SDL_Surface *surface);
  void Show_Text( int x, int y, std::string source, SDL_Surface *surface);

  void Apply_Surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
  uint32_t Get_Pixel32( int x, int y, SDL_Surface *surface);

};

