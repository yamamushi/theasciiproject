/*

  The ASCII Project - Client

  December 5th, 2012
  -Yamamushi@gmail.com

  
  Our portable SDL-based client


 */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "graphics/BitmapFont.h"
#include "graphics/ClientWindow.h"
#include "io/ClientKeyboard.h"
#include "audio/Mixer.h"
#include "graphics/Window.h"

#include <string>


int main(int argc, char* argv[]){

  ClientWindow *clientWindow = new ClientWindow();

  if( SDL_Flip( clientWindow->mainScreen ) == -1){
    return 1;
  }


  Mixer *loadingMusic = new Mixer();
  loadingMusic->Load_Music( (char *)"data/audio/Loading.mp3" );
  loadingMusic->Music_Volume( MIX_MAX_VOLUME / 2);
  loadingMusic->Fade_In_Music( 45000 );
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

    SDL_Color greenColor;
    greenColor.r = 50;
    greenColor.g = 205;
    greenColor.b = 50;

    SDL_Color blackColor;
    blackColor.r = 0;
    blackColor.g = 0;
    blackColor.b = 0;

    SDL_Color purpleColor;
    purpleColor.r = 100;
    purpleColor.g = 50;
    purpleColor.b = 100;

    clientWindow->fontHandler->Set_Character_Color( greenColor, true );
    clientWindow->fontHandler->Set_Character_Color( blackColor, false );
    

    clientWindow->fontHandler->Show_Text( ( clientWindow->mainScreen->w / 2 ) - (fontTestString.length()), clientWindow->mainScreen->h / 2, fontTestString, clientWindow->mainScreen);
    
    
    clientWindow->fontHandler->Set_Character_Color( purpleColor , false);
    clientWindow->fontHandler->Show_Text( 50, 50, L"\u256C\u256C\u256C\n\u256C\u256C\u256C", clientWindow->mainScreen);


    if( SDL_Flip( clientWindow->mainScreen ) == -1 ){
      return 1;
    }

  }

  delete loadingMusic; 
  delete clientWindow;

  
  return 0;

}
