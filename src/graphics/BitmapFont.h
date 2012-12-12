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
  
  // Used for storing the offsets in character spacing
  int newLine, space;

  // Used as references when changing character colors
  uint32_t foreColor, backColor;


 public:

  BitmapFont();
  BitmapFont( SDL_Surface *surface);

  void Build_Font( SDL_Surface *surface);

  // This is a basic function that does wstring drawing
  // Without Color Support
  void Show_Text( int x, int y, std::wstring source, SDL_Surface *surface);

  // This is our Magic Colored String Drawing Function
  void Show_Colored_Text( int x, int y, SDL_Color ForeColor, SDL_Color BackColor, std::wstring source, SDL_Surface *destination);

  // Removed as this does dangerous things and is 
  // EXTREMELY inefficient, use Print_Colored_Character instead.
  // void Set_Font_Color(SDL_Color color, bool fore = true);

  void Print_Colored_Character( wchar_t character, SDL_Color ForeColor, SDL_Color BackColor, int X, int Y, SDL_Surface *destination);

  void Apply_Surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );


};

