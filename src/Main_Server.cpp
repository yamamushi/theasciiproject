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
#include "Headers.h"
#include "ServerSocket.h"


Entity *test;




// Lets's Rock n' Roll

int main(int argc, char *argv[]){
        
    TileMap *map = new TileMap(MAP_WIDTH, MAP_HEIGHT);    
    // Temporary Dungeon Generator
    Dungeon::Dungeon(map, MAP_WIDTH, MAP_HEIGHT, true);    
    // init Fov Lib ASAP after TileMap and Dungeon have been initialized.
    FovLib *fovLib = new FovLib(map);
    // Obviously our entity map would depend on FOV being loaded.
    EntityMap *entMap = new EntityMap(MAP_WIDTH, MAP_HEIGHT, map, fovLib);
    
    Entity *player = new Player();
    Goblin *goblin = new Goblin();
    
    // Entities don't have to be initialized at the same time, they can
    // also be initialized individually.
    entMap->addToMap(player);
    entMap->initAllEnts();
    entMap->addToMap(goblin);
    
    goblin->move(map->rooms[5]->cX, map->rooms[5]->cY);
    player->move(map->rooms[1]->cX, map->rooms[1]->cY);
    
    RenderMap *rMap = new RenderMap(map, entMap);
    player->associateClient(rMap);    
    rMap->refreshMap();
        
    test = player;

    
    try
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), 5250);
        game_server server(io_service, endpoint);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
        
    
    
    return 0;
}
