/*

  The ASCII Project - Client

  December 5th, 2012
  -Yamamushi@gmail.com

  
  Our portable SDL-based client


 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "graphics/ClientWindow.h"
#include <string>


int main(int argc, char* argv[]){

  SDL_Surface *screen = nullptr;
  SDL_Surface *hello = nullptr;

  ClientWindow *clientWindow = new ClientWindow();

  screen = SDL_SetVideoMode( 1024, 748, 32, SDL_SWSURFACE);
  hello = IMG_Load( "data/hello.bmp" );

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
