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
//colorTable *cTable = new colorTable(true);


int main(
	int argc, char *argv[]) {


	// boring variables
	bool quit = false;
	CenterX = MAIN_WIDTH/2;
	CenterY = MAIN_HEIGHT/2;

	int i, x, y, z;
	
	// Let's get things setup
	
	// TCODConsole::credits();
	
	Keyboard *kboard = new Keyboard();

	// We'll set the foreground color once now and modify it as necessary when in our game loop
	
	Map *map = new Map(MAP_WIDTH, MAP_HEIGHT);
	GraphicsTCOD *output = new GraphicsTCOD(map);

	Dungeon *dgn = new Dungeon(map, MAP_WIDTH, MAP_HEIGHT, true);


	Entity *player = new Entity( "@", TCODColor::white);
	
	// Create an npc, for testing purposes only, this will be moved!
	Entity *npc = new Entity( "@", TCODColor::red);

	Entity **tArray[2];
	tArray[0] = &player;
	tArray[1] = &npc;
	
	Entity * scan;
	int ray;
	int si = sizeof tArray/sizeof(Entity **);
	

	// lets build our map o_o;;
	int pX = map->rooms[1]->cX;
	int pY = map->rooms[1]->cY;	
	
	player->move(pX, pY);
	kboard->initKeyboard(pX, pY);
	
	int nX = map->rooms[10]->cX;
	int nY = map->rooms[10]->cY;	

	npc->move(nX, nY);

	TCODMap *tcodMap = new TCODMap(MAP_WIDTH, MAP_HEIGHT);

	//output->render();

	for(x = 0; x < MAP_WIDTH; x++){
		for(y = 0; y < MAP_HEIGHT; y++){
			tcodMap->setProperties(x, y, !(map->virtMap[x][y]->block_sight), !(map->virtMap[x][y]->blocked));
		}
	}
	
	
	// Main Game Loop
	while(!TCODConsole::isWindowClosed()) {

		// Draw our map to the screen
		output->render();
		if(map->checkBounds(kboard->safX, kboard->safY)){
				kboard->passSafeCursor();
				player->move(kboard->curX, kboard->curY);
				tcodMap->computeFov( player->posX, player->posY, TORCH_RADIUS, FOV_LIGHT_WALLS);
				for(x=0; x < MAP_WIDTH; x++){
					for(y=0; y < MAP_HEIGHT; y++){
						if((tcodMap->isInFov(x,y))){
							map->virtMap[x][y]->visible = true;
							map->virtMap[x][y]->explored = true;
						}
						else {
							map->virtMap[x][y]->visible = false;
						}
					}
				}
		}

		// Do some quick boundary checks
		// Draw our entities to the screen	
		for ( ray = 0; ray < si; ray++){
			scan = *tArray[ray];
			scan->draw(output->output);
		}	

		TCODConsole::blit(output->output, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
		TCODConsole::flush();
	
		
		
		// Clean up our screen before reading in keys
		for ( ray=0; ray < si; ray++){
			scan = *tArray[ray];
			scan->clean(output->output);
		}	

		quit = kboard->handleKeys();
		if(quit) break;		

	}	

	return 0;
}
