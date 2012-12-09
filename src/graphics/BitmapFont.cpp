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
     for( int rows = 0; rows < 2048; rows++){
       for( int cols = 0; cols < 32; cols++){

         chars[currentChar] = new SDL_Rect;

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
         for( int pRow = 0; pRow < cellH; pRow++ ){
           for( int pCol = 0; pCol < cellW; pCol++ ){

             // Pixel offsets
             int pX = ( cellW * cols ) + pCol;
             int pY = ( cellH * rows ) + pRow;
             
             // Check color-key
             if( Get_Pixel32( pX, pY, bitmap) != bgColor ){

               // If new top is found
               if( pRow < top ){
                 top = pRow;
               }

               // Break the loop
               pCol = cellW;
               pRow = cellH;

             }
           }
         }

         // Find bottom of A
         if( currentChar == 'A' ){
           for( int pRow = cellH - 1; pRow >= 0; pRow--){
             for( int pCol = 0; pCol < cellW; pCol++){
               
               // Get the pixel offsets
               int pX = ( cellW * cols ) + pCol;
               int pY = ( cellH * rows ) + pRow;

               // If a non color-key pixel is found...
               if( Get_Pixel32( pX, pY, bitmap) != bgColor ){
                 
                 // Bottom of 'a' is found
                 baseA = pRow;
                 
                 // Break loops
                 pCol = cellW;
                 pRow = -1;
               }
             }
          }
          } 
           // Go to next character
           currentChar++;    

         }
       }

      
       // Calculate space
       space = cellW / 2;
       
       // Calculate newline
       newLine = baseA - top;
       
       // Lop off excess top pixels
       for( int t = 0; t < 65536; t++ ){
         chars[t]->y += top;
         chars[t]->h -= top;
       }

}



void BitmapFont::Show_Text( int x, int y, std::string source, SDL_Surface *surface){

    //Temp offsets
  int X = x, Y = y;

  //If the font has been built
  if( bitmap != NULL )
    {
      //Go through the text
      for( int show = 0; show < source.length(); show++ )
        {
          //If the current character is a space
          if( source[ show ] == ' ' )
            {
              //Move over
              X += space;
            }
          //If the current character is a newline
          else if( source[ show ] == '\n' )
            {
              //Move down
              Y += newLine;
              
              //Move back
              X = x;
            }
          
          //Get the ASCII value of the character
          int ascii = (unsigned char)source[ show ];
          
          //Show the character
          Apply_Surface( X, Y, bitmap, surface, chars[ ascii ] );
          
          //Move over the width of the character with one pixel of padding
          X += chars[ ascii ]->w + 1;
        }
    }
} 



void BitmapFont::Apply_Surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip){

  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  
  SDL_BlitSurface( source, clip, destination, &offset);

}



uint32_t BitmapFont::Get_Pixel32( int x, int y, SDL_Surface *surface){

//Convert the pixels to 32 bit
  uint32_t *pixels = (uint32_t *)surface->pixels;

//Get the pixel requested
  return pixels[ ( y * surface->w ) + x ];

}
