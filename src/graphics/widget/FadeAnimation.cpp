/*

  FadeAnimation

  Our FadeAnimation Widget

*/

#include "../Frame.h"
#include "FadeAnimation.h"
#include "SDL/SDL.h"


FadeAnimation::FadeAnimation( Frame *owner, SDL_Surface *from, SDL_Surface *to, float length) : Widget(owner) {

  timespan = length;
  initialSurface = from;
  endSurface = to;

};
