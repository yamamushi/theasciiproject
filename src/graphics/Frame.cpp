/*

  Frame
  
  Our Frame Functions

  -Yamamushi (Jon Rumion)
  2012 - 12 -10

*/

#include "Frame.h"
#include "widget/Widget.h"
#include "SDL/SDL.h"


Frame::Frame( int Width, int Height, int PosX, int PosY){

  width = Width;
  height = Height;
  posX = PosX;
  posY = PosY;

  sdlScreen = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
  drawThisFrame = false;
  removeThisFrame = false;

}


void Frame::Render_Widgets(){

  for( int i = 0; i < widgetList.size(); i++){
    

  }

}




