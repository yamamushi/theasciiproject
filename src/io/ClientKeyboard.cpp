/*
 
 ClientKeyboard
 
 This file holds our ClientKeyboard functions
 
 */


#include "ClientKeyboard.h"
#include "../graphics/ClientWindow.h"
#include "../graphics/Window.h"
#include <iostream>


ClientKeyboard::ClientKeyboard(ClientWindow *host){
    
    clientWindow = host;
    
}



void ClientKeyboard::Handle_Keys(SDL_Event event){
    
    clientWindow->mainWindow->Add_To_Event_Queue( event );
    
};
