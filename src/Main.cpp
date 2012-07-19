/*
 * =====================================================================================
 *
 *       Filename:  Main.cpp
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








// Lets's Rock n' Roll

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

	TileMap *map = new TileMap(MAP_WIDTH, MAP_HEIGHT);
	Dungeon *dgn = new Dungeon(map, MAP_WIDTH, MAP_HEIGHT, true);

	EntityMap *entMap = new EntityMap(MAP_WIDTH, MAP_HEIGHT);
	Entity *player = new Player();
	Goblin *goblin = new Goblin();
        Goblin *goblinA = new Goblin();


	entMap->addToMap(goblin);
        entMap->addToMap(goblinA);
	entMap->addToMap(player);


	entMap->initAllEnts(map);

	int pX = map->rooms[1]->cX;
	int pY = map->rooms[1]->cY;

	player->move(map, pX, pY);
	goblin->move(map, pX-1, pY-1);
        goblinA->move(map, pX+1, pY+1);


	//entMap->refreshEntityMap();
	kboard->initKeyboard(pX, pY);

        RenderMap *rMap = new RenderMap(map, entMap);
	GraphicsTCOD *output = new GraphicsTCOD(rMap);


	TCODMap *tcodMap = new TCODMap(MAP_WIDTH, MAP_HEIGHT);

	for(x = 0; x < MAP_WIDTH; x++){
		for(y = 0; y < MAP_HEIGHT; y++){
			tcodMap->setProperties(x, y, !(map->virtMap[x][y]->block_sight), !(map->virtMap[x][y]->blocked));
		}
	}


	// Main Game Loop
	while(!TCODConsole::isWindowClosed()) {

		// Compute FOV
		tcodMap->computeFov( player->posX(), player->posY(), TORCH_RADIUS, FOV_LIGHT_WALLS);
				for(x=0; x < MAP_WIDTH; x++){
					for(y=0; y < MAP_HEIGHT; y++){
						if((tcodMap->isInFov(x,y))){
							map->virtMap[x][y]->visible = true;
							map->virtMap[x][y]->explored = true;
							player->fov[x][y] = true;
						}
						else {
							map->virtMap[x][y]->visible = false;
							player->fov[x][y] = false;
						}
					}
				}


                entMap->refreshEntityMap();
                rMap->refreshMap();
		output->render();

		output->clearScreen();
		quit = kboard->handleKeys(player, map);
		if(quit) break;

	}

	return 0;
}
