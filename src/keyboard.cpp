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
 * =====================================================================================
 */
#include "libtcod.hpp"

bool handleKeys(){

	TCOD_key_t Key = TCODConsole::checkForKeypress(true);
	bool quit = false;
	extern int playerX, playerY;


	if(Key.vk == TCODK_ENTER && Key.lalt)
		TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
	
	switch(Key.vk)
	{
	       	case TCODK_UP:
			playerY--;
			break;	
		case TCODK_DOWN:																              playerY++;
		  	break;
																			              case TCODK_LEFT:
			playerX--;				                        
			break;	
																				      case TCODK_RIGHT:
			playerX++;
			break;
																				      case TCODK_ESCAPE:
			quit = true;
			break;

	}
	return quit;

}

