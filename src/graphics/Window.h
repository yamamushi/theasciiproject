/*

  Window

  A container for Window events, ie. this enables us to resize our window.



 */

#include "SDL/SDL.h"


class Window {

 private:

  // Whether the window is windowed or not
  bool windowed;

  // Window status
  bool windowOK;


 public:
  
  Window();
  virtual ~Window(){};

  // Our SDL Window for this Object
  SDL_Surface *screen;

  
  void Handle_Events(SDL_Event event);
  void Toggle_Fullscreen();

  // Our generic Error Handling Function
  bool Error();

};
