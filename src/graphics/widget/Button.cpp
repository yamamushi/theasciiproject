/*

  Button

  Our functions for our Button Widget
  -Yamamushi (Jon Rumion)
  12-18-2012

*/

#include "SDL/SDL.h"

#include "../Frame.h"
#include "Button.h"
#include "Widget.h"

#include <iostream>
#include <string>


Button::Button( Frame *owner, int PosX, int PosY, std::wstring OnText, std::wstring OffText, SDL_Color OnColor, SDL_Color OffColor) : Widget(owner) {

  posX = PosX;
  posY = PosY;

  onText = OnText;
  offText = OffText;

  onColor = OnColor;
  offColor = OffColor;

}


void Button::Update( Frame *caller ){

  if(caller->Check_Focus()){

    std::cout << "Button Frame Now Has Focus" << std::endl;

  }

}




void Button::Handle_Event( SDL_Event event ){

 

}
