/*
 * =====================================================================================
 *
 *       Filename:  ClientWidgets.h
 *
 *    Description:  This object defines the behavior of our "Entities", ie
 *                  The necessary functions for an entity to exist on the "Map"
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:41:29 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yamamushi (Jon Rumion)
 *   Organization:  The ASCII Project
 *
 *	  License:  GPLv3
 *
 *	  Copyright 2012 Jonathan Rumion
 *
 *   This file is part of The ASCII Project.
 *
 *   The ASCII Project is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   The ASCII Project is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with The ASCII Project.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * =====================================================================================
 */



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
