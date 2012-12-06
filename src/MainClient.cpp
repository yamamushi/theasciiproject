/*

  The ASCII Project - Client

  December 5th, 2012
  -Yamamushi@gmail.com

  
  Our portable SDL-based client


 */


#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"


// Ignore this stuff, it's only here to test automake
// ie, to make sure automake is linking sdl_* stuff properly.
TTF_Font *font = NULL;
SDL_Color textcolor = {255, 255, 255};


int main(int argc, char *argv[]){

  std::cout << "Testing Client" << std::endl;

  return 0;

}
