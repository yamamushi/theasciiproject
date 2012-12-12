/*

  BitmapFont Class functions
  -Yamamushi

  Adapted from http://lazyfoo.net/SDL_tutorials/lesson30/index.php

 */

#include "Pixels.h"
#include "BitmapFont.h"


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <string>
#include <iostream>



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
     uint32_t bgColor = SDL_MapRGB( bitmap->format, 0x00, 0x00, 0x00);
backColor = ::Get_Pixel32( 0, 0, bitmap);
     foreColor = 0xFFFFFF;

     SDL_SetColorKey( bitmap, SDL_SRCCOLORKEY, SDL_MapRGB( bitmap->format, 0, 0, 0) );

     // Character Cell dimensions
     int cellW = bitmap->w / 32;
     int cellH = bitmap->h / 2048;

     // New Line Variables
     int top = cellH;
     int baseA = cellH;

     // The current chars[%] value we're setting
     int currentChar = 0;

     // Start by cell rows
     for( int rows = 0; rows < 2048; rows++){
       for( int cols = 0; cols < 32; cols++){

         chars[currentChar] = new SDL_Rect;

         // Start by setting our Character offsets
         chars[currentChar]->x = cellW * cols;
         chars[currentChar]->y = cellH * rows;

         // Set character dimensions
         chars[currentChar]->w = cellW;
         chars[currentChar]->h = cellH;

         // Go to next character
         currentChar++;    
         
       }
     }
     
     // Calculate space
     space = cellW;
     newLine = cellH;

}



void BitmapFont::Show_Text( int x, int y, std::wstring source, SDL_Surface *surface){

    //Temp offsets
  int X = x, Y = y;

  //If the font has been built
  if( bitmap != NULL )
    {
      //Go through the text
      for( int show = 0; show < source.length(); show++ )
        {
          //If the current character is a space
          /*  if( source[ show ] == ' ' )
            {
              //Move over
              X += space;
            } */
          //If the current character is a newline
          if( source[ show ] == '\n' )
            {
              //Move down
              Y += newLine;
              
              //Move back
              X = x - chars[0]->w;
            }
          else{
          //Get the ASCII value of the character
          int ascii = (wchar_t)source[ show ];
          
          //Show the character
          Apply_Surface( X, Y, bitmap, surface, chars[ ascii ] );
          }
    
          //Move over the width of the character with one pixel of padding
          X += chars[ 0 ]->w;
          
        }
    }
} 



void BitmapFont::Set_Font_Color(SDL_Color color, bool fore){

  uint32_t *pixels = (uint32_t *)bitmap->pixels;

  SDL_LockSurface( bitmap );

  if(fore){
    for(int i = 0; i < bitmap->w * bitmap->h; i++){
      if( pixels[i] !=  backColor ){
        
        pixels[i] = SDL_MapRGB( bitmap->format, color.r, color.g, color.b);
        
      }    
    }
    foreColor = SDL_MapRGB( bitmap->format, color.r, color.g, color.b);        
  }
  else{
    for(int i = 0; i < bitmap->w * bitmap->h; i++){
      if( pixels[i] != foreColor ){
        
        pixels[i] = SDL_MapRGB( bitmap->format, color.r, color.g, color.b);
        
      }
    }
    backColor = SDL_MapRGB( bitmap->format, color.r, color.g, color.b);
  }

    SDL_UnlockSurface( bitmap );
}



void BitmapFont::Print_Colored_Character( wchar_t character, SDL_Color color, int X, int Y, SDL_Surface *destination, bool fore){

  int index = character;


  SDL_Surface *tmpSurface = SDL_CreateRGBSurface( SDL_SWSURFACE, chars[index]->w, chars[index]->h, bitmap->format->BitsPerPixel, bitmap->format->Rmask, bitmap->format->Gmask, bitmap->format->Bmask, 0);

  SDL_LockSurface( tmpSurface );

  int changey = 0;
  int changex = 0;

  for ( int y = chars[index]->y; y < (chars[index]->h + chars[index]->y); ++y) 
    {

      for ( int x = chars[index]->x; x < (chars[index]->w + chars[index]->x); ++x) 
        {
          
          uint32_t copyPixel = ::Get_Pixel32( x, y, bitmap);
          ::Put_Pixel32( changex, changey, copyPixel, tmpSurface);
          changex++;
        }
      changex = 0;
      changey++;
    }


  // Afterwards, we color tmpSurface and apply it
  // To the screen at the requested x, y offsets

  uint32_t *pixels = (uint32_t *)tmpSurface->pixels;

  if(fore){
    for(int i = 0; i < tmpSurface->w * tmpSurface->h; i++){
      if( pixels[i] !=  backColor ){
        
        pixels[i] = SDL_MapRGB( tmpSurface->format, color.r, color.g, color.b);
        
      }    
    }
  }
  else{
    for(int i = 0; i < tmpSurface->w * tmpSurface->h; i++){
      if( pixels[i] != foreColor ){
        
        pixels[i] = SDL_MapRGB( tmpSurface->format, color.r, color.g, color.b);
        
      }
    }
  }

  SDL_UnlockSurface( tmpSurface );

  SDL_Rect offset;
  offset.x = X;
  offset.y = Y;

  Apply_Surface( X, Y, tmpSurface, destination);
  
}




void BitmapFont::Apply_Surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip){

  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  if( SDL_BlitSurface( source, clip, destination, &offset) < 0 ){
    std::cout << "Apply Surface: Blit Error" << std::endl;
  }

}




