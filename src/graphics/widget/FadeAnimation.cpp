/*

  FadeAnimation

  Our FadeAnimation Widget

*/

#include "../../utils/Timer.h"
#include "../Frame.h"
#include "FadeAnimation.h"
#include "SDL/SDL.h"

#include <iostream>

FadeAnimation::FadeAnimation( Frame *owner, SDL_Surface *from, SDL_Surface *to, float length) : Widget(owner) {

  timespan = length;
  initialSurface = from;
  endSurface = to;

  keyDownWait = false;
  keyUpWait = false;

  ticks = 0.0;
  alphaPerSecond = (255.0 / timespan);
  currentAlpha = 0;

  clock = new Timer();
  clock->start();

  SDL_SetAlpha( endSurface, SDL_SRCALPHA, currentAlpha);
  SDL_BlitSurface( endSurface, NULL, initialSurface, NULL);
  
};


void FadeAnimation::Update(Frame *caller){

  ticks = clock->get_ticks();
  clock->start();

  elapsed += ticks / 1000.0f;

  currentAlpha += alphaPerSecond * elapsed;
  
  if(currentAlpha > 255)
    currentAlpha = 255;
  
  SDL_SetAlpha( endSurface, SDL_SRCALPHA, currentAlpha);
  uint32_t black = SDL_MapRGB( endSurface->format, 0, 0, 0);
  SDL_FillRect( initialSurface, NULL, black);
  SDL_BlitSurface( endSurface, NULL, initialSurface, NULL);
  
}


bool FadeAnimation::IsComplete(){

  if( currentAlpha >= 255)
    return true;
  else
    return false;

}


void FadeAnimation::Handle_Event( SDL_Event event ){

  if( (event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_UP) ){
      keyUpWait = true;
  }
  if( (event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_UP) ){
    if(keyUpWait){
      std::cout << "Up Key Event Detected by FadeAnimation" << std::endl;
      keyUpWait = false;
    }
  }
}
