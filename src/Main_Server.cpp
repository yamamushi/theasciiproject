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


// Lets's Rock n' Roll

int main(int argc, char *argv[]){

    // boring variables
    bool quit = false;
    int CenterX = MAIN_WIDTH / 2;
    int CenterY = MAIN_HEIGHT / 2;

    int i, x, y, z;

    // Temporary variable (see Entities.cpp)
    extern unsigned int UIDList;

    // Let's get things setup
    Keyboard *kboard = new Keyboard();

    TileMap *map = new TileMap(MAP_WIDTH, MAP_HEIGHT);

    // Temporary Dungeon Generator
    Dungeon *dgn = new Dungeon(map, MAP_WIDTH, MAP_HEIGHT, true);

    // init Fov Lib ASAP after TileMap and Dungeon have been initialized.
    FovLib *fovLib = new FovLib(map);

    // Obviously our entity map would depend on FOV being loaded.
    EntityMap *entMap = new EntityMap(MAP_WIDTH, MAP_HEIGHT, map, fovLib);

    Entity *player = new Player();
    Goblin *goblin = new Goblin();

    entMap->addToMap(player);
    entMap->initAllEnts();

    // Entities don't have to be initialized at the same time, they can
    // also be initialized individually.
    entMap->addToMap(goblin);

    goblin->move(map->rooms[5]->cX, map->rooms[5]->cY);
    player->move(map->rooms[1]->cX, map->rooms[1]->cY);

    RenderMap *rMap = new RenderMap(map, entMap);
//    player->associateClient(rMap);

    // Main Game Loop

    StdoutLog log;
    LocalSocketHandler h(&log);

    // line server
    ListenSocket<DisplaySocketMenu> lSock(h);
    lSock.Bind(1066);
    h.Add(&lSock);

    h.Select(1, 0);

    while(!h.Quit()){

        h.Select(1, 0);

    }


    return 0;
}
