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
#include "map.h"
#include "entities.h"
#include "keyboard.h"
#include "colors.h"

// Followed by standard headers
#include <math.h>

// size of the heightmap
#define MAIN_WIDTH 100
#define MAIN_HEIGHT 80

#define MAP_WIDTH 80
#define MAP_HEIGHT 60

#define LIMIT_FPS 20

// We'll probably move these global variables somewhere else later
int CenterX, CenterY;


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

	entity *player = new entity(CenterX, CenterY, "@", TCODColor::white);
	
	// Create an npc, for testing purposes only, this will be moved!
	entity *npc = new entity(CenterX+1, CenterY+1, "@", TCODColor::red);

	entity **tArray[2];
	tArray[0] = &player;
	tArray[1] = &npc;
	
	entity * scan;
	int ray;
	int si = sizeof tArray/sizeof(entity **);
	
	colorTable *cTable = new colorTable(true);

	// lets build our map o_o;;
	
	int i, x, y, z;
	Tile * mapArray[MAP_WIDTH][MAP_HEIGHT];

	for ( x = 0; x < MAP_WIDTH; x++){
		for ( y = 0; y < MAP_HEIGHT; y++){
			mapArray[x][y] = new Tile(false);
		}
	}
	
	mapArray[30][22]->init_Tile(true);
	mapArray[50][22]->init_Tile(true);



	// Main Game Loop

	while(!TCODConsole::isWindowClosed()) {

		// some crude but effective boundaries checking
		if (mapArray[player->posX][player->posY]->is_blocked() || player->posX <= 0 || player->posX >= MAP_WIDTH || player->posY < 0 || player->posY >= MAP_HEIGHT){
			player->posX = kboard->oldX;
			player->posY = kboard->oldY;
		}
			
		// Draw our map to the screen
		for(x=0;x<MAP_WIDTH;x++){
			for(y=0;y<MAP_HEIGHT;y++){
				if (mapArray[x][y]->is_sight_blocked())
					con->setCharBackground(x, y, cTable->dark_wall, TCOD_BKGND_SET);
				else
					con->setCharBackground(x, y, cTable->dark_ground, TCOD_BKGND_SET);
			}
		}


		// Draw our entities to the screen	
		for ( ray = 0; ray < si; ray++){
			scan = *tArray[ray];
			scan->draw(con);
		}	

		
		TCODConsole::flush();
		TCODConsole::blit(con, 1, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);

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
