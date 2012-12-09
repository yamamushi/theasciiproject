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
         chars[currentChar]->y = cellH * rows;

         // Set character dimensions
         chars[currentChar]->w = cellW;
         chars[currentChar]->h = cellH;
         
         // Now we set the individual box dimensions
         // Starting with the left side...
         for( int pCol = 0; pCol < cellW; pCol++){
           for( int pRow = 0; pRow < cellH; pRow++){
             
             // Now our pixel offsets
             int pX = (cellW * cols) + pCol;
             int pY = (cellH * rows) + pRow;

             // If a non color-key pixel is found
             if( Get_Pixel32( pX, pY, bitmap ) != bgColor ){

               // Set the X offset
               chars[currentChar]->x = pX;
               
               // Do this to break our for-loops
               pCol = cellW;
               pRow = cellH;
               
             }
           }
         }
         
         // And now the right side, which we do from right to left
         for( int pCol_w = cellW - 1; pCol_w >= 0; pCol_w--){
           for( int pRow_w = 0; pRow_w < cellH; pRow_w++){
             
             // Get the pixel offsets
             int pX = ( cellW * cols ) + pCol_w;
             int pY = ( cellH * rows ) + pRow_w;

             // Once again, if a non color-key pixel is found
             if( Get_Pixel32( pX, pY, bitmap ) != bgColor ){
               
               // Set the width
               chars[currentChar]->w = ( pX - chars[currentChar]->x) + 1;
               
               // Break the loop
               pCol_w = -1;
               pRow_w = cellH;
               
             }
           }
         }

         // Now we get the top by pixel rows
         


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

