/*
 * =====================================================================================
 *
 *       Filename:  keyboard.c
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

#include "libtcod.hpp"
#include "keyboard.h"
#include "entities.h"

bool handleKeys(){

	TCOD_key_t Key = TCODConsole::checkForKeypress(true);
	bool quit = false;
	extern int CenterX, CenterY;


	if(Key.vk == TCODK_ENTER && Key.lalt)
		TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
	
	switch(Key.vk)
	{
	       	case TCODK_UP:
			CenterY--;
			break;

		case TCODK_DOWN:
			CenterY++;
		  	break;
			
		case TCODK_LEFT:
			CenterX--;				                        
			break;	
			
		case TCODK_RIGHT:
			CenterX++;
			break;

		case TCODK_ESCAPE:
			quit = true;
			break;

	}
	return quit;

}

