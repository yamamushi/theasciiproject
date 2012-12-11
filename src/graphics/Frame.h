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

  Frame();
  virtual ~Frame(){ if(sdlScreen){ delete sdlScreen;} };

  bool drawThisFrame;
  bool removeThisFrame;

  int posX, posY;

  SDL_Surface *sdlScreen;

  void Render_Widgets();

};

