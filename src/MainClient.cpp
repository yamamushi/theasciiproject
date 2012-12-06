/*

  The ASCII Project - Client

  December 5th, 2012
  -Yamamushi@gmail.com

  
  Our portable SDL-based client


 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>


int main(int argc, char* argv[]){

  SDL_Surface *screen = nullptr;
  SDL_Surface *hello = nullptr;

  SDL_Init(SDL_INIT_EVERYTHING);

  screen = SDL_SetVideoMode( 1024, 748, 32, SDL_SWSURFACE);

  hello = IMG_Load( "hello.bmp" );

  SDL_WM_SetCaption( "The ASCII Project - Client - 0.0.1f", NULL );
  SDL_BlitSurface( hello, nullptr, screen, nullptr);

  SDL_Flip( screen );

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
  SDL_Quit();

  return 0;

}
