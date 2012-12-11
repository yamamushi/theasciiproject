/*

  Frame
  
  Our Frame Functions

  -Yamamushi (Jon Rumion)
  2012 - 12 -10

*/

#include "Frame.h"
#include "widget/Widget.h"
#include "SDL/SDL.h"


Frame::Frame(){

  sdlScreen = nullptr;
  drawThisFrame = false;
  removeThisFrame = false;

}


void Frame::Render_Widgets(){

  for( int i = 0; i < widgetList.size(); i++){
    

  }

}




