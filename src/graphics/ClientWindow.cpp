/*

  ClientWindow (.cpp)
  

 */

#include "ClientWindow.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


ClientWindow::ClientWindow(){

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption( "The ASCII Project - Client - 0.0.1f", NULL);


}


void ClientWindow::ClientWindowUpdate(SDL_Surface *source, SDL_Surface *destination){

  SDL_BlitSurface(source, nullptr, destination, nullptr);

  SDL_Flip(destination);

}


ClientWindow::~ClientWindow(){

  SDL_Quit();

}
