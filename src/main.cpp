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
//
#include "headers.h"


// We'll probably move these global variables somewhere else later
int CenterX, CenterY;
colorTable *cTable = new colorTable(true);


int main(
	int argc, char *argv[]) {


	// boring variables
	bool quit = false;
	CenterX = MAIN_WIDTH/2;
	CenterY = MAIN_HEIGHT/2;

	
	// Let's get things setup
	
	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false,TCOD_RENDERER_SDL);
	// TCODConsole::credits();
	
	TCODConsole *con = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);

	
	TCODSystem::setFps(LIMIT_FPS);

	Keyboard *kboard = new Keyboard();

	// We'll set the foreground color once now and modify it as necessary when in our game loop
	TCODConsole::root->setDefaultForeground(TCODColor::white);	

	entity *player = new entity( 25, 23, "@", TCODColor::white);
	
	// Create an npc, for testing purposes only, this will be moved!
	entity *npc = new entity(CenterX+1, CenterY+1, "@", TCODColor::red);

	entity **tArray[2];
	tArray[0] = &player;
	tArray[1] = &npc;
	
	entity * scan;
	int ray;
	int si = sizeof tArray/sizeof(entity **);
	

	// lets build our map o_o;;
	
	int i, x, y, z;

	Map *map = new Map(MAP_WIDTH, MAP_HEIGHT);
	map->createRoom(20, 15, 10, 15);
	map->createRoom(50, 15, 10, 15);
	map->createHall(25, 55, 23);


	Dungeon *dungeon = new Dungeon(map);

	// Main Game Loop
	while(!TCODConsole::isWindowClosed()) {

		// Do some quick boundary checks
		map->checkBounds(player, kboard);
		// Draw our map to the screen
		map->drawMap(con);
		// Draw our entities to the screen	
		for ( ray = 0; ray < si; ray++){
			scan = *tArray[ray];
			scan->draw(con);
		}	

		TCODConsole::blit(con, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
		TCODConsole::flush();
		
		
		
		// Clean up our screen before reading in keys
		for ( ray=0; ray < si; ray++){
			scan = *tArray[ray];
			scan->clean(con);
		}	

		quit = kboard->handleKeys(player);
		if(quit) break;		

	}	

	return 0;
}
