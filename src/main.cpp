/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  The ASCII Project main loop
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:04:46 AM
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

// First our custom headers
#include "libtcod.hpp"
#include "keyboard.h"
#include "entities.h"
#include "map.h"

// Followed by standard headers
#include <math.h>

// size of the heightmap
#define MAIN_WIDTH 100
#define MAIN_HEIGHT 80

#define LIMIT_FPS 20

// We'll probably move these global variables somewhere else later
int playerX, playerY;


int main(
	int argc, char *argv[]) {


	// boring variables
	bool quit = false;
	playerX = MAIN_WIDTH/2;
	playerY = MAIN_HEIGHT/2;

	
	// Let's get things setup
	
	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false,TCOD_RENDERER_SDL);
	// TCODConsole::credits();
	
	TCODConsole *con = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);

	
	TCODSystem::setFps(LIMIT_FPS);


	// We'll set the foreground color once now and modify it as necessary when in our game loop
	TCODConsole::root->setDefaultForeground(TCODColor::white);	

	entity *player = new entity(playerX, playerY, "@", TCODColor::white);
	
	// Create an npc, for testing purposes only, this will be moved!
	entity *npc = new entity(playerX+1, playerY+1, "@", TCODColor::red);

	entity **tArray[2];
	tArray[0] = &player;
	tArray[1] = &npc;
	
	entity * scan;
	int ray = 0;
	int si = sizeof tArray/sizeof(entity **);

	while(!TCODConsole::isWindowClosed()) {
		
		player->move(playerX, playerY);

		// Draw our entities to the screen	
		for ( ray = 0; ray < si; ray++){
			scan = *tArray[ray];
			scan->draw(con);
		}	

		
		TCODConsole::flush();
		TCODConsole::blit(con, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);

		// Clean up our screen before reading in keys
		for ( ray=0; ray < si; ray++){
			scan = *tArray[ray];
			scan->clean(con);
		}	

		quit = handleKeys();
		if(quit) break;		

	}	

	return 0;
}
