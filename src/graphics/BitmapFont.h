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

#include "Pixels.h"
#include <string>
#include "SDL/SDL.h"


class BitmapFont {

 private:

  // Our font surface, aka this will point to font.png 
  SDL_Surface *bitmap;
  // All Unicode Characters in the font accounted for
  SDL_Rect *chars[65536];
  
  int newLine, space;

  uint32_t foreColor, backColor;


 public:

  BitmapFont();
  BitmapFont( SDL_Surface *surface);

  void Build_Font( SDL_Surface *surface);
  void Show_Text( int x, int y, std::wstring source, SDL_Surface *surface);
  
  void Set_Font_Color(SDL_Color color, bool fore = true);
  void Print_Colored_Character( wchar_t character, SDL_Color color, int X, int Y, SDL_Surface *destination, bool fore = true);

  void Apply_Surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
  uint32_t Get_Pixel32( int x, int y, SDL_Surface *surface);

};

