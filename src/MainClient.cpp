/*

  The ASCII Project - Client

  December 5th, 2012
  -Yamamushi@gmail.com

  
  Our portable SDL-based client


 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "audio/Mixer.h"

#include "graphics/BitmapFont.h"
#include "graphics/ClientWindow.h"
#include "graphics/Window.h"

#include <string>


int main(int argc, char* argv[]){

  ClientWindow *clientWindow = new ClientWindow();

  if( SDL_Flip( clientWindow->mainScreen ) == -1){
    return 1;
  }
  // This is only here for my memory, ignore it!
  //  clientWindow->ClientWindowUpdate(hello, screen);

  Mixer loadingMusic;
  loadingMusic.Load_Music( (char *)"data/audio/Loading.mp3" );
  loadingMusic.Music_Volume( MIX_MAX_VOLUME );
  loadingMusic.Fade_In_Music( 25000 );
  // We know music playing works
  // loadingMusic.Play_Music();
    

  bool quit = false;
  SDL_Event event;
  while( quit == false){
    while(SDL_PollEvent( &event )){
      
      clientWindow->mainWindow->Handle_Events( event );

      if( (event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ) ){
        quit = true;
      }

      if( event.type == SDL_QUIT){
        quit = true;
      }
    }

    if( clientWindow->mainWindow->Error() == true ){
      return 1;
    }

    std::wstring fontTestString = L"Bitmap Font Test \n\u263a \u2190 Should be a Smiley Face";

    clientWindow->fontHandler->Show_Text( ( clientWindow->mainScreen->w / 2 ) - (fontTestString.length()), clientWindow->mainScreen->h / 2, fontTestString, clientWindow->mainScreen);



    if( SDL_Flip( clientWindow->mainScreen ) == -1 ){
      return 1;
    }

  }

  delete clientWindow;

  return 0;

}
