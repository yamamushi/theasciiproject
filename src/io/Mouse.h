/*
 
 Mouse
 
 A class for handling our Mouse input events
 -Yamamushi (Jon Rumion)
 2012 - 12 - 12
 
 */

#include "SDL/SDL.h"

class ClientWindow;


class Mouse {
    
private:
    
    ClientWindow *parentClient;
    
public:
    
    Mouse( ClientWindow *parentWindow) : parentClient(parentWindow) {};
    virtual ~Mouse(){};
    
    void Handle_Mouse_Input( SDL_Event event );
    
};

