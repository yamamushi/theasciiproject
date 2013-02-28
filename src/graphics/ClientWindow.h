#pragma once
/*
  
  ClientWindow

  This object controls the initial Window setup for the Client, as
  well as window resizing.

 */

class BitmapFont;
class SDL_Surface;
class Window;


class ClientWindow {

 private:

  SDL_Surface *fontFile;
  

 public:

  ClientWindow();
  virtual ~ClientWindow();

  BitmapFont *fontHandler;
  Window *mainWindow;
  SDL_Surface *mainScreen;

  void Init();
  bool InitSDL();

  void ClientWindowUpdate(SDL_Surface *source, SDL_Surface *destination);
  
};
