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

  SDL_Surface *sdlScreen;

  std::vector<Widget *> widgetList;

 public:

  Frame();
  virtual ~Frame(){};


};
