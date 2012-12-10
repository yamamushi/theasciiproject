/*

  ClientWindow (.cpp)
  

 */

#include "BitmapFont.h"
#include "ClientWindow.h"
#include "Window.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"



ClientWindow::ClientWindow(){

  Init();
    
}



void ClientWindow::Init(){

  // Start SDL Engine
  InitSDL();

  // Create our "global" resizable window
  mainWindow = new Window();
  mainScreen = mainWindow->screen;

  // Load up our font file and the Handler
  fontFile = IMG_Load( "data/font.png" );
  fontHandler = new BitmapFont( fontFile );

}


bool ClientWindow::InitSDL(){

  if(SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
    return false;
  }
  
  return true;

}


void ClientWindow::ClientWindowUpdate(SDL_Surface *source, SDL_Surface *destination){

  SDL_BlitSurface(source, nullptr, destination, nullptr);

  SDL_Flip(destination);

}


ClientWindow::~ClientWindow(){

  SDL_Quit();

}
