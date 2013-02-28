/*

  ClientKeyboard

  This naming convention is used as opposed to "Keyboard", as there
  are also methods for input to the server on the console, thus this
  should avoid any confusion about the matter.

  -Yamamushi (Jon Rumion)
  2012 - 12 - 11

 */

#include "SDL/SDL.h"

class ClientWindow;


class ClientKeyboard {

 private:

  ClientWindow *clientWindow;


 public:

  ClientKeyboard(ClientWindow *host);
  virtual ~ClientKeyboard(){};

  void Handle_Keys(SDL_Event event);

};
