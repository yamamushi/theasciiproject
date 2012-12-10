/*

  The ASCII Project - Client

  December 5th, 2012
  -Yamamushi@gmail.com

  
  Our portable SDL-based client


 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "graphics/ClientWindow.h"
#include "graphics/BitmapFont.h"

int main(int argc, char* argv[]){


  ClientWindow *clientWindow = new ClientWindow();
  SDL_Surface *screen = SDL_SetVideoMode( 1024, 640, 32, SDL_SWSURFACE);
  SDL_Surface *bitmapFont = IMG_Load( "data/font.png" );
  //SDL_SetColorKey( bitmapFont, SDL_SRCCOLORKEY, SDL_MapRGB( bitmapFont->format, 0, 0xFF, 0xFF));

  BitmapFont font( bitmapFont );
  //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ));
  font.Show_Text( 100, 100, L"Bitmap Font Test \u263a", screen );

  if( SDL_Flip( screen ) == -1){
    return 1;
  }

  //  clientWindow->ClientWindowUpdate(hello, screen);

  bool quit = false;
  SDL_Event event;
  while( quit == false){
    while(SDL_PollEvent( &event )){
      if( event.type == SDL_QUIT){
        quit = true;
      }
    }
  }
   
  //  SDL_FreeSurface( hello );

  delete clientWindow;

  return 0;

}
