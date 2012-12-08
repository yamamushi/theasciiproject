/*

  The ASCII Project - Client

  December 5th, 2012
  -Yamamushi@gmail.com

  
  Our portable SDL-based client


 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "graphics/ClientWindow.h"


int main(int argc, char* argv[]){


  ClientWindow *clientWindow = new ClientWindow();
  SDL_Surface *screen = SDL_SetVideoMode( 1024, 640, 32, SDL_SWSURFACE);
  SDL_Surface *hello = IMG_Load( "data/font.png" );

  clientWindow->ClientWindowUpdate(hello, screen);

  bool quit = false;
  SDL_Event event;
  while( quit == false){
    while(SDL_PollEvent( &event )){
      if( event.type == SDL_QUIT){
        quit = true;
      }
    }
  }
   
  SDL_FreeSurface( hello );

  delete clientWindow;

  return 0;

}
