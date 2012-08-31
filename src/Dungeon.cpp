/*
 * =====================================================================================
 *
 *       Filename:  Dungeon.cpp
 *
 *    Description:  Our dungeon generator
 *
 *        Version:  1.0
 *        Created:  07/05/2012
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


#include "libtcod/libtcod.hpp"
#include "constants.h"
#include "Dungeon.h"

#include "TileMap.h"


Dungeon::Dungeon(TileMap *destination, int width, int height, bool create = false){
    
    
	initDungeon(destination, width, height, create);
    
}


void	Dungeon::initDungeon(TileMap *destination, int width, int height, bool create = false){
    
	if (width > MAP_WIDTH || height > MAP_HEIGHT)
		return;
    
	destMap = destination;
	TileMap *dungeonMap = new TileMap(width, height);
    
	if (create){
		createRooms( MAX_ROOMS, ROOM_MIN_SIZE, ROOM_MAX_SIZE, dungeonMap);
		connectRooms(dungeonMap);
        
		destMap->importMap(dungeonMap);
	}
}







bool	Dungeon::createRooms(int numberOfRooms, int minSize, int maxSize, TileMap *outputMap){
    
    
	if (numberOfRooms > MAX_ROOMS)
		return false;
	else if (minSize < ROOM_MIN_SIZE || maxSize > ROOM_MAX_SIZE)
		return false;
    
	TCODRandom *rng = new TCODRandom();
	dungeonMap = outputMap;
    
	i = 0;
	bool test;
    
    
    
	while(i < numberOfRooms){
		w = rng->getInt(minSize, maxSize);
		h = rng->getInt(minSize, maxSize);
		// checks for map boundaries
		x = rng->getInt( 0, MAP_WIDTH - w - 3);
		y = rng->getInt( 0, MAP_HEIGHT - h - 3);
        
		tempRoom = new Room(x, y, w, h);
        
		test = false;
		// if it's our first room, we import it to our test map and move along
        
		// now we go through the list of rooms that exist
		// in our temporary map
        
		if (i > 0)
            for(x=0; x < i; x++){
                
                if(tempRoom->doesIntersect(dungeonMap->rooms[x]))
                    test = true;
			}
        
		if(!test){
			dungeonMap->importRoom(tempRoom);
			i++;
		}
        
	}
    
    
	delete rng;
	return true;
    
}








void Dungeon::connectRooms(TileMap *outputMap){
    
	TileMap *dungeonMap = outputMap;
    
	i = dungeonMap->numRooms;
    
	TCODRandom *rng = new TCODRandom();
    
	//x = rng->getInt(5, 30);
	//y = rng->getInt(5, 30);
	//w = 5
    
	int prev_x, prev_y, new_x, new_y;
    
    
	for ( x = 0; x < i; x++){
        
        
		if (x != 0){
			prev_x = dungeonMap->rooms[x-1]->cX;
			prev_y = dungeonMap->rooms[x-1]->cY;
			new_x = dungeonMap->rooms[x]->cX;
			new_y = dungeonMap->rooms[x]->cY;
            
			if ((rng->getInt(0, 1)) == 1){
				dungeonMap->createHall(prev_x, new_x, prev_y, 0);
				dungeonMap->createHall(prev_y, new_y, new_x, 1);
			}
			else {
				dungeonMap->createHall(prev_y, new_y, prev_x, 1);
				dungeonMap->createHall(prev_x, new_x, new_y, 0);
			}
		}
	}
    
	delete rng;
    
}





























