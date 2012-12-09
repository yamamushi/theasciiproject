/*

  ClientWindow (.cpp)
  

 */

#include "ClientWindow.h"
#include "BitmapFont.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"



ClientWindow::ClientWindow(){

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption( "The ASCII Project - Client - 0.0.1f", NULL);

  // I guess now is a good time to start loading our massive font
  // Delegated to our BitmapFont class.
  

}


void ClientWindow::ClientWindowUpdate(SDL_Surface *source, SDL_Surface *destination){

  SDL_BlitSurface(source, nullptr, destination, nullptr);

  SDL_Flip(destination);

}


ClientWindow::~ClientWindow(){

  SDL_Quit();

}
