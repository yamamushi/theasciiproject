/*

  ClientKeyboard

  This file holds our ClientKeyboard functions

*/


#include "ClientKeyboard.h"
#include "../graphics/ClientWindow.h"
#include <iostream>


ClientKeyboard::ClientKeyboard(ClientWindow *host){

  clientWindow = host;

}



void ClientKeyboard::Handle_Keys(SDL_Event event){

  std::cout << "Keyboard Input" << std::endl;

};
