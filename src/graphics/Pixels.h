#pragma once
/*
  
  Pixels

  A set of functions for working with Pixels
  -Yamamushi (Jon Rumion)
  2012 - 12 - 12


 */

#include "SDL/SDL.h"



#if defined __UINT32_MAX__ or UINT32_MAX
#include <inttypes.h>
#else
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
#endif

namespace pixels {
  uint32_t Get_Pixel32( int x, int y, SDL_Surface *surface);
  void Put_Pixel32( int x, int y, uint32_t pixel, SDL_Surface *surface);
}
