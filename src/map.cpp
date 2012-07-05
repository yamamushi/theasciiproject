/*
 * =====================================================================================
 *
 *       Filename:  map.c
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
}


Room::Room(int x, int y, int w, int h){
	initRoom(x, y, w, h);
}

void Room::initRoom(int x, int y, int w, int h){
	extern Tile * mapArray[MAP_WIDTH][MAP_HEIGHT];
	Rect *dim = new Rect(x, y, w, h);

	
	for(x = dim->x2; x > dim->x1+1;x--){
		for(y = dim->y2; y > dim->y1+1; y--){
			mapArray[x][y]->blocked = false;
			mapArray[x][y]->block_sight = false;
		}
	}

}


Hall::Hall(int x, int y, int z){
	initHall( x, y, z);
}

void Hall::initHall( int x, int y, int z){
	extern Tile * mapArray[MAP_WIDTH][MAP_HEIGHT];
	int x1, x2;
	x1 = min(x, y);
	x2 = max(x, y);

	for( x1 = x1; x1 < x2; x1++){
		mapArray[x1][z]->blocked = false;
		mapArray[x1][z]->block_sight = false;
	}
}



Map::Map(int i, int z){
	initMap(i, z);
}

void Map::initMap(int i, int z){
	extern Tile * mapArray[MAP_WIDTH][MAP_HEIGHT];
	numRooms = 0;


	for ( x = 0; x < i; x++){
		for ( y = 0; y < z; y++){
			mapArray[x][y] = new Tile(true);
	       	}	
	}
}



void Map::drawMap(TCODConsole *dest){

	extern Tile * mapArray[MAP_WIDTH][MAP_HEIGHT];
	extern colorTable *cTable;


	for(x=0;x<MAP_WIDTH;x++){
		for(y=0;y<MAP_HEIGHT;y++){
			if (mapArray[x][y]->is_sight_blocked())
				dest->setCharBackground(x, y, cTable->dark_wall, TCOD_BKGND_SET);
			else
				dest->setCharBackground(x, y, cTable->dark_ground, TCOD_BKGND_SET);      
		}
	}
}



void Map::checkBounds(entity *target, Keyboard *buffer){
	Keyboard kboard = *buffer;
	entity *tgt = target;
	extern Tile * mapArray[MAP_WIDTH][MAP_HEIGHT];	

	if (mapArray[tgt->posX][tgt->posY]->is_blocked() || tgt->posX <= 0 || tgt->posX >= MAP_WIDTH || tgt->posY < 0 || tgt->posY >= MAP_HEIGHT){
			tgt->posX = kboard.oldX;
			tgt->posY = kboard.oldY;
		}
}



void Map::createRoom(int x, int y, int z, int i){
	Room *room = new Room(x, y, z, i);
	
	delete room;
}


void Map::createHall(int x, int y, int z){
	Hall *hall = new Hall(x, y, z);
	delete hall;
}













