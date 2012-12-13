#pragma once
/*

  Widget

  Used for storing, well, Widgets!

  -Yamamushi (Jon Rumion)
  2012 - 12 - 10

 */

#include "../Frame.h"
#include "SDL/SDL.h"




class Widget {

 private:

 public:

  Widget(Frame *tgt){ frameSurface = tgt->sdlScreen; };
  virtual ~Widget(){};

  SDL_Surface *frameSurface;
  virtual void Run() =0;
  virtual void Update() =0;
  virtual void Handle_Event( SDL_Event event ) =0;
    
};

