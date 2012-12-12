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
#include "graphics/Frame.h"
#include "graphics/widget/Widget.h"
#include "graphics/widget/FadeAnimation.h"
#include "audio/Mixer.h"
#include "graphics/Window.h"
#include "utils/Timer.h"

#include <string>


//The frames per second
const int FRAMES_PER_SECOND = 20;




int main(int argc, char* argv[]){


  /* 
     We first create our ClientWindow under the easy-to-remember
     name, 'clientWindow'. 

     ClientWindow is a container, consider it the glue between
     Our Keyboard Input, Character Drawing, Resizable Windows
     and screens.

     +----------Client Window--------+
     |                               |<--------> Keyboard
     | +-----------Window----------+ |      Handles Keyboard input
     | +                           + |
     | +  +------mainScreen------+ + |<--------> BitmapFont
     | +  |                      | + |      Handles our Font Rendering
     | +  |                      | + |
     | +  |                      | + |<--------> Window
     | +  +----------------------+ + |      Used for Window Size
     | +                           + |      Management.
     | +---------------------------+ |
     |                               |<--------> mainScreen
     +-------------------------------+      The Main Screen upon which
                                            The screens from Frames
                                            are drawn.

   */
  ClientWindow *clientWindow = new ClientWindow();
  if( SDL_Flip( clientWindow->mainScreen ) == -1){
    return 1;
  }

  /*

    Mixer is a very simple container for playing sound, of course it
    can be improved rather easily, which I may or may not get around
    to doing before 2013.

   */

  Mixer *loadingMusic = new Mixer();
  loadingMusic->Load_Music( (char *)"data/audio/Loading.mp3" );
  loadingMusic->Music_Volume( MIX_MAX_VOLUME / 2);
  loadingMusic->Fade_In_Music( 20000 );
  
  




  /*
    
    We load an image into an SDL_Surface (screen) , which 
    automatically scales to the size of the image being loaded.

   */

  SDL_Surface *testImage = IMG_Load("data/loading.png");



  /*

    We then pass our "testImage" screen properties, which contains the image
    located at 'data/loading.png', as arguments to the Frame class to
    create a new frame.

    Each frame is a container for various bits of information, such as
    an SDL_Surface * . 

    Note that we don't initialize the frame with a screen, but rather
    we use width and height values as parameters to let the Frame know
    how much space it occupies on the mainScreen.

    Now, 

    +-------------------mainScreen-----------------+
    +                                              + 
    +  +-----Frame----------+  +--Frame--+ +-Frm+  + 
    +  +                    +  +         + +    +  + 
    +  +                    +  +         + +    +  + 
    +  +                    +  +         + +    +  + 
    +  +                    +  +         + +    +  + 
    +  +                    +  +         + +    +  + 
    +  +--------------------+  +---------+ +----+  + 
    +                                              + 
    +  +-----------------Frame------------------+  + 
    +  +                                        +  + 
    +  +                                        +  + 
    +  +                                        +  + 
    +  +----------------------------------------+  + 
    +                                              + 
    +----------------------------------------------+


   */

  Frame *testFrame = new Frame( clientWindow->mainScreen->w, clientWindow->mainScreen->h);
  FadeAnimation *testAnimate = new FadeAnimation( testFrame, testFrame->sdlScreen, testImage, 4000);

  // One event object to track input from here out
  // One event object to rule them all
  SDL_Event event;

  // A simple timer object for restricting FPS, the framerate is
  // regulated by const int's at the top of this file
  Timer fps;
  
  // Our Loading Screen Animation
  bool finishedLoading = false;
  while( !finishedLoading ){
    fps.start();
    if(SDL_PollEvent( &event )){
      //clientWindow->mainWindow->Handle_Events( event );
      
      if(( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE )){
        finishedLoading = true;
      }
      else if( event.type == SDL_QUIT ){
        finishedLoading = true;
      }
    }
  
    if( clientWindow->mainWindow->Error() == true ){
      return 1;
    }

    // Our Animation Goes Here
    //clientWindow->mainWindow->Draw_Frames();
    testAnimate->Update();

    SDL_Rect tmpRect;
    tmpRect.x = (clientWindow->mainScreen->w - testFrame->sdlScreen->w) / 2;
    tmpRect.y = (clientWindow->mainScreen->h - testFrame->sdlScreen->h) / 2;
    SDL_BlitSurface( testFrame->sdlScreen, NULL, clientWindow->mainScreen, &tmpRect);

    if(testAnimate->IsComplete()){
      finishedLoading = true;
    }

    if( SDL_Flip( clientWindow->mainScreen ) == -1 ){
      return 1;
    }

    if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
      SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    }

  }
  
  // Some quick font fixing stuff
  SDL_Color blackColor;
  blackColor.r = 0;
  blackColor.g = 0;
  blackColor.b = 0;

  SDL_Color greenColor;
  greenColor.r = 50;
  greenColor.g = 205;
  greenColor.b = 50;


  bool quitMain = false;
  while( !quitMain ){
    fps.start();
    while(SDL_PollEvent( &event )){
      
      clientWindow->mainWindow->Handle_Events( event );

      if( (event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ) ){
        quitMain = true;
      }

      if( event.type == SDL_QUIT){
        quitMain = true;
      }
    }

    if( clientWindow->mainWindow->Error() == true ){
      return 1;
    }

    wchar_t tmpChar = L'\u263A';

    // We use this as opposed to "Show_Text" as it enables us to print
    // colored strings
    clientWindow->fontHandler->Show_Colored_Text( 50, 50, greenColor, blackColor, L"\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n\u2551 The ASCII Project \u2551\n\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D", clientWindow->mainScreen);

    // Remember that calls to Print_Colored_Character REQUIRE fore and
    // back color arguments
    clientWindow->fontHandler->Print_Colored_Character( tmpChar, greenColor, blackColor, 120, 120, clientWindow->mainScreen);

    if( SDL_Flip( clientWindow->mainScreen ) == -1 ){
      return 1;
    }
    
    if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
      SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    }

  }

  delete loadingMusic; 
  delete clientWindow;
  
  return 0;

}
