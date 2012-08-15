/*
 * =====================================================================================
 *
 *       Filename:  Graphics.h
 *
 *    Description:  Our graphics handling library that relies on libtcod.
 *    		The intention is for this library to handle all reliance on
 *    		the libtcod graphics functions - thereby slowly modularilizing
 *    		the client to be rendered differently.
 *
 *        Version:  1.0
 *        Created:  07/05/2012
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


class ClientSession;



class GraphicsTCOD {
    
private:
    
    TileMap *input;
    ClientMap *cMap;
    TCODText *inputText;
    float H, S, V, HD, SD, VD;
    float TH, TS, TV, THD, TSD, TVD;

    
    VBox *menuPopup;
    
    
public:
    
    
    TCODConsole *output;
    TCODConsole *widgetCon;
    TCODConsole *offscreenConsole;
    TCODConsole *textOutputConsole;
    
    bool rendering;
    
    GraphicsTCOD(ClientMap *clientMap);
    void init(ClientMap *clientMap);
    
    static void loginCbk(Widget *w, void *userData);  
    static void quitCbk(Widget *w, void *userData);
    static void menuCbk(Widget *w, void *userData);
    static void closeMenuCbk(Widget *w, void *userData);
    
    void drawMenu();
    void drawMainInterface();
    
    void getUser();
    void getPassword();
    
    void loginError();
    
    void newAccountMenu(Widget *w, void *data);
    void quitMenu(Widget *w, void *data);
    
    void fixBottom();
    
    void drawAt(int x, int y);
    void drawAll();
    
    void render();
    void flushScreen();
    
    void prepare(int x, int y);
    void clearScreen();
    
    
};
























