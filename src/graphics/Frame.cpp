/*

  Frame
  
  Our Frame Functions

  -Yamamushi (Jon Rumion)
  2012 - 12 -10

*/

#include "Frame.h"
#include "Pixels.h"
#include "widget/Widget.h"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_rotozoom.h"


Frame::Frame( int Width, int Height, int PosX, int PosY){

  width = Width;
  height = Height;
  posX = PosX;
  posY = PosY;

  sdlScreen = SDL_CreateRGBSurface( 0, width, height, 32, 0, 0, 0, 0);
  drawThisFrame = false;
  removeThisFrame = false;
  //  queuedEvent = nullptr;

}


void Frame::Add_Widget(Widget *newWidget){

  widgetList.push_back(newWidget);

}


void Frame::Render_Widgets(){

  for( int i = 0; i < widgetList.size(); i++){
  
    if( widgetList.at(i) != nullptr ){

      if( hasFocus ){
        widgetList.at(i)->Handle_Event( queuedEvent );
      }

      widgetList.at(i)->Update();

    }
  }

}



void Frame::SetPos( int x, int y){

  posX = x;
  posY = y;

}



void Frame::Resize( int w, int h){

  if(width != w || height != h ){
    width = w;
    height = h;
    
    double zoomx = w / (float)sdlScreen->w;
    double zoomy = h / (float)sdlScreen->h;

    SDL_Surface* sized = zoomSurface( sdlScreen, zoomx, zoomy, SMOOTHING_ON );
    //    matchColorKeys( sdlScreen, sized);
    if( sdlScreen->flags & SDL_SRCCOLORKEY )
      {
        Uint32 colorkey = sdlScreen->format->colorkey;
        SDL_SetColorKey( sized, SDL_SRCCOLORKEY, colorkey );
      }

    sdlScreen = sized;

  }
}


void Frame::Handle_Event( SDL_Event event ){
  
  queuedEvent = event;

}


void Frame::Set_FrameList_Index( int i ){

  frameListIndex = i;

}



int Frame::Get_FrameList_Index(){

  return frameListIndex;

}


void Frame::Set_Focus(bool toggle){

  hasFocus = toggle;

}


bool Frame::Check_Focus(){

  return hasFocus;

}
