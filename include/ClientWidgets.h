#pragma once

#include <string>
#include <vector>

#include "libtcod/gui/gui.hpp"

class TCODConsole;
class GraphicsTCOD;
class ClientMap;

class ScrollBox : public Widget {
    
private:
    
    std::vector<std::string> *textBuffer;
    char *scrollbackBuffer;
    
    int maxBuffer;
    int scrollBuffer;
    int realX;
    int realY;
    
    bool acceptCommands;
    
    
    TCODConsole *console;
    GraphicsTCOD *graphics;
    ClientMap *clientMap;
    
public :
    
    bool connected;
    
    ScrollBox( int x, int y, int w, int h, int MaxBuffer, TCODConsole *Console, ClientMap *cMap, GraphicsTCOD *graphicsEngine);
    virtual ~ScrollBox();
    void attachConsole(TCODConsole *Console);
    void render();
    void update(const TCOD_mouse_t k);
    void insertText(std::string newText);
    
    void setRealPosition(int x, int y);
    void takeCommands(bool accept);
    
    static void connectServer(ClientMap *cMap, GraphicsTCOD *graphicsEngine);
    
protected :
    
    bool onUpArrow;
    bool onDownArrow;
    bool scrollUp;
    bool scrollDown;
    
    
    
        
    void onButtonPress();
    void onButtonRelease();
    void onScrollUp();
    void onScrollDown();
};
