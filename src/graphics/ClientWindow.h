#pragma once
/*
  
  ClientWindow

  This object controls the initial Window setup for the Client, as
  well as window resizing.

 */

class SDL_Surface;


class ClientWindow {

 private:


 public:

  ClientWindow();
  virtual ~ClientWindow();


  void ClientWindowUpdate(SDL_Surface *source, SDL_Surface *destination);
  


};
