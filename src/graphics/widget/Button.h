#pragma once
/*

  Button
  -Yamamushi (Jon Rumion)
  12-18-2012

  A simple button state with an on-off color state, a text to display
  for both states, and a callback to perform when pressed/selected.

  The callback MUST be a function with NO arguments

*/

#include "SDL/SDL.h"

#include "../Frame.h"
#include "Widget.h"

#include <string>

class Button : public Widget {

 private:

  int posX, posY;
  bool hasFocus;
  std::wstring onText, offText;

  SDL_Color onColor, offColor;

 public:

  Button( Frame *owner, int PosX, int PosY, std::wstring OnText, std::wstring OffString, SDL_Color OnColor, SDL_Color OffColor);
  virtual ~Button(){};

  virtual void Run(){};
  virtual void Update(Frame *caller);
  virtual void Handle_Event( SDL_Event event);

};
