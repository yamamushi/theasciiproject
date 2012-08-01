/*
 * =====================================================================================
 *
 *       Filename:  FovLib.cpp
 *
 *    Description:  This library handles FOV calculations for entities.
 *
 *        Version:  1.0
 *        Created:  07/19/2012 07:42:00 PM
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

#include "Headers.h"




FovLib::FovLib(TileMap *map){
    
    initFovLib(map);
    
}


void FovLib::initFovLib(TileMap *map){
    
    tcodMap = new TCODMap(MAP_WIDTH, MAP_HEIGHT);
    tileMap = map;
    
    int x, y;
    
    for(x = 0; x < MAP_WIDTH; x++){
        for(y = 0; y < MAP_HEIGHT; y++){
            tcodMap->setProperties(x, y, !(map->virtMap[x][y]->block_sight), !(map->virtMap[x][y]->blocked));
        }
    }
    
    
}


void FovLib::refreshFov(Entity *tgt){
    
    int x, y;
    
    // Compute FOV
    tcodMap->computeFov(tgt->posX(), tgt->posY(), TORCH_RADIUS, FOV_LIGHT_WALLS, FOV_ALGO);
    
    for (x = 0; x < MAP_WIDTH; x++)
    {
        for (y = 0; y < MAP_HEIGHT; y++)
        {
            
            if ((tcodMap->isInFov(x, y)))
            {
                if (tgt->getAssociated())
                {
                    ClientMap *clientMap = tgt->returnCMap();
                    clientMap->cMap[x][y]->visible = true;
                    clientMap->cMap[x][y]->explored = true;
                    
                }
                tgt->fov[x][y] = true;
            }
            else
            {
                if (tgt->getAssociated())
                {
                    ClientMap *clientMap = tgt->returnCMap();
                    clientMap->cMap[x][y]->visible = false;
                    clientMap->cMap[x][y]->occupied = false;
                }
                tgt->fov[x][y] = false;
            }
        }
    }
    
}


TileMap *FovLib::getTileMap(){
    
    return tileMap;
    
}