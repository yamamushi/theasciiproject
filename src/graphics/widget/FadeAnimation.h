/*

  FadeAnimation

  This Widget Fades One SDL_Surface to Another based on time

  -Yamamushi (Jon Rumion)
  2012 - 12 - 11

*/

#include "Widget.h"
#include "SDL/SDL.h"

class Frame;
class Timer;


class FadeAnimation : public Widget {

private:

  int timespan;
  float alphaPerSecond;
  int currentAlpha;
  float elapsed;
  float ticks;

  SDL_Surface *initialSurface;
  SDL_Surface *endSurface;

  Timer *clock;


public:

  FadeAnimation( Frame *owner, SDL_Surface *from, SDL_Surface *to, float length);

  virtual ~FadeAnimation(){};


  void Update();
  bool IsComplete();

};
