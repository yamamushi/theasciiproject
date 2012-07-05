/*
 * =====================================================================================
 *
 *       Filename:  map.cpp
 *
 *    Description:  Our map drawing functions (will be replaced)
 *
 *        Version:  1.0
 *        Created:  07/03/2012 07:51:39 AM
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

#include "headers.h"

using namespace std;





Tile::Tile(bool blked){
	init_Tile(blked);
}

void Tile::init_Tile(bool blked){
	blocked = blked;
	if(blked)
		block_sight = true;
	else
		block_sight = false;
}

bool Tile::is_sight_blocked(){
	return block_sight;
}

bool Tile::is_blocked(){
	return blocked;
}




Rect::Rect(int x, int y, int w, int h){
	initRect(x, y, w, h);
}

void Rect::initRect(int x, int y, int w, int h){
	
	
	x1 = x;
	y1 = y;
	x2 = x + w;
	y2 = y + h;

	cX = (x1+x2)/2;
	cY = (y1+y2)/2;
}







Room::Room(int x, int y, int w, int h){
	initRoom(x, y, w, h);
}


void Room::initRoom(int x, int y, int w, int h){
	
	Rect *dim = new Rect(x, y, w, h);
	
	x1 = dim->x1;
	x2 = dim->x2;
	y1 = dim->y1;
	y2 = dim->y2;

	cX = dim->cX;
	cY = dim->cY;

}




Map::Map(int i, int z){
	initMap(i, z);
}

void Map::initMap(int i, int z){
	numRooms = 0;

	for ( x = 0; x < i; x++){
		for ( y = 0; y < z; y++){
			virtMap[x][y] = new Tile(true);
	       	}	
	}
}



void Map::drawMap(TCODConsole *dest){
	extern colorTable *cTable;

	for(x=0;x<MAP_WIDTH;x++){
		for(y=0;y<MAP_HEIGHT;y++){
			if (virtMap[x][y]->is_sight_blocked())
				dest->setCharBackground(x, y, cTable->dark_wall, TCOD_BKGND_SET);
			else
				dest->setCharBackground(x, y, cTable->dark_ground, TCOD_BKGND_SET);      
		}
	}
}



void Map::checkBounds(entity *target, Keyboard *buffer){
	Keyboard kboard = *buffer;
	entity *tgt = target;

	if (virtMap[tgt->posX][tgt->posY]->is_blocked() || tgt->posX <= 0 || tgt->posX >= MAP_WIDTH || tgt->posY < 0 || tgt->posY >= MAP_HEIGHT){
			tgt->posX = kboard.oldX;
			tgt->posY = kboard.oldY;
		}
}



void Map::createRoom(int x, int y, int z, int i){
	rooms[numRooms] = new Room(x, y, z, i);
	numRooms++;
}	






void Map::drawRoom(int i){

	for(x = rooms[i]->x2; x > rooms[i]->x1+1; x--){
		for(y = rooms[i]->y2; y > rooms[i]->y1+1; y--){
			virtMap[x][y]->blocked = false;
			virtMap[x][y]->block_sight = false;
		}
	}
}



void Map::drawAllRooms(){
	
	for(i=0; i < numRooms; i++){
		for(x = rooms[i]->x2; x > rooms[i]->x1+1; x--){
			for(y = rooms[i]->y2; y > rooms[i]->y1+1; y--){
				virtMap[x][y]->blocked = false;
				virtMap[x][y]->block_sight = false;
			}
		}
	}


}


void Map::createHall(int x, int y, int z){
	int x1, x2;
	x1 = min(x, y);
	x2 = max(x, y);

	for( x1 = x1; x1 < x2; x1++){
		virtMap[x1][z]->blocked = false;
		virtMap[x1][z]->block_sight = false;
	}
}


