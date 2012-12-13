#pragma once
/*
  Frame

  A class for storing Widgets and other items to be
  Easily moved around a Window Container

  -Yamamushi (Jon Rumion)
  2012 - 12 - 10

 */


#include "SDL/SDL.h"

#include <vector>

class Widget;



class Frame {

 private:

  std::vector<Widget *> widgetList;

 public:

  Frame( int Width, int Height, int PosX=0, int PosY=0);
  virtual ~Frame(){ if(sdlScreen){ delete sdlScreen;} };

  bool drawThisFrame;
  bool removeThisFrame;

  int width, height;
  int posX, posY;

  SDL_Surface *sdlScreen;

  void Add_Widget(Widget *newWidget);
  void Render_Widgets();

};

