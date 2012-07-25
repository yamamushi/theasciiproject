/*
 * =====================================================================================
 *
 *       Filename:  Keyboard.cpp
 *
 *    Description:  Our keyboard input functions
 *
 *        Version:  1.0
 *        Created:  07/03/2012 02:35:13 AM
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


#include "headers.h"



Keyboard::Keyboard(int x, int y){
	initKeyboard(x, y);
}

void Keyboard::initKeyboard(int x, int y){
    
	curX = x;
	curY = y;
	safX = x;
	safY = y;
    
}


bool Keyboard::handleKeys(){
    
	TCOD_key_t Key = TCODConsole::checkForKeypress(true);
	bool quit = false;
    
    
	//Entity *tgt = target;
    
    
	if(Key.vk == TCODK_ENTER && TCODK_ALT)
		TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
    
	switch(Key.vk)
	{
            /*   	case TCODK_UP:
             //tgt->move(0,-1);
             break;
             
             case TCODK_DOWN:
             //tgt->move(0,1);
             break;
             
             case TCODK_LEFT:
             //tgt->move(-1,0);
             break;
             
             case TCODK_RIGHT:
             //tgt->move(1,0);
             
             break; */
            
		case TCODK_ESCAPE:
			quit = true;
			break;
            
	}
	return quit;
    
}



void Keyboard::safeMoveCursor(int sx, int sy){
    
	safX = curX;
	safY = curY;
    
	safX += sx;
	safY += sy;
    
}

void Keyboard::passSafeCursor(){
    
	curX = safX;
	curY = safY;
    
}




void Keyboard::moveCursor(int mx, int my){
    
	curX += mx;
	curY += my;
    
}


void Keyboard::placeCursor( int x, int y){
    
	curX = x;
    curY = y;
    
}







