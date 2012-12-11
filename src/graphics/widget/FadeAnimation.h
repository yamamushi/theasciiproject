/*

  FadeAnimation

  This Widget Fades One SDL_Surface to Another based on time

  -Yamamushi (Jon Rumion)
  2012 - 12 - 11

*/

#include "Widget.h"
#include "SDL/SDL.h"

class Frame;


class FadeAnimation : public Widget {

private:

  float timespan;
  float elapsed;
  int alphaPerSecond;

  SDL_Surface *initialSurface;
  SDL_Surface *endSurface;


public:

  FadeAnimation( Frame *owner, SDL_Surface *from, SDL_Surface *to, float length);

  virtual ~FadeAnimation(){};


};
