/*
 * =====================================================================================
 *
 *       Filename:  TileMap.cpp
 *
 *    Description:  This object stores the positions of Tiles on the Map.
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



#include "Headers.h"


TileMap::TileMap(int i, int z){
	initMap(i, z);
}

void TileMap::initMap(int i, int z){
	numRooms = 0;
	numHalls = 0;
	wid = i;
	hig = z;
    
    
	for ( x = 0; x < i; x++){
		for ( y = 0; y < z; y++){
			virtMap[x][y] = new Wall();
        }
	}
    
}

void TileMap::clearMap(){
    
	for (x = 0; x < MAP_WIDTH; x++){
		for ( y = 0; y < MAP_HEIGHT; y++){
			delete virtMap[x][y];
			virtMap[x][y] = new Wall(true);
		}
	}
    
}

void TileMap::refreshMap(){
    
	for (x=0; x < wid; x++){
		for ( y = 0; y < hig; y++){
			virtMap[x][y] = new Wall();
		}
	}
    
}

bool TileMap::checkBounds(int posX, int posY){
    
	if (virtMap[posX][posY]->isBlocked() || posX <= 0 || posX >= MAP_WIDTH || posY < 0 || posY >= MAP_HEIGHT)
		return false;
	else
		return true;
}

void TileMap::createRoom(int x, int y, int z, int i){
    
	rooms[numRooms] = new Room(x, y, z, i);
	numRooms++;
    
}

void TileMap::drawRoom(int i){
    
	for(x = rooms[i]->x2; x > rooms[i]->x1+1; x--){
		for(y = rooms[i]->y2; y > rooms[i]->y1+1; y--){
			delete virtMap[x][y];
			virtMap[x][y] = new Floor;
		}
	}
}

void TileMap::drawAllRooms(){
    
	for(z=0; z < numRooms; z++){
		drawRoom(z);
	}
    
}

void TileMap::createHall(int x, int y, int z, int dir){
    
	halls[numHalls] = new Hall(x, y, z, dir);
	numHalls++;
    
}

void TileMap::drawHall(int i){
    
	if ( (halls[i]->dir) == 0){
		for( x = halls[i]->x1; x < halls[i]->x2; x++){
			delete virtMap[x][halls[i]->y];
			virtMap[x][halls[i]->y] = new Floor;
		}
	}
	else {
		for( x = halls[i]->x1; x < halls[i]->x2 + 1; x++){
			delete virtMap[halls[i]->y][x];
			virtMap[halls[i]->y][x] = new Floor;
		}
	}
    
}

void TileMap::drawAllHalls(){
    
	for(z=0; z < numHalls; z++){
		drawHall(z);
	}
}

void TileMap::orientWalls(){
    
    int x, y;
    unsigned int TypeID;
    
    for(x=1; x < (MAP_WIDTH - 1) ; x++){
        for(y=1; y < (MAP_HEIGHT - 1); y++){
            TypeID = virtMap[x][y]->getTypeID();
            Tile *center = virtMap[x][y];
            
            // Now for some really crappy calculations that should
            // And will be rewritten in a less craptastic manner.
            if (TypeID == 1){
                if(TypeID == (virtMap[x-1][y]->getTypeID()) ) {
                    
                    
                    
                    // ═
                    
                    if(TypeID == (virtMap[x+1][y]->getTypeID())){
                        center->setOrientation(0);
                    }
                    
                    
                    // ║ for left side walls
                    
                    if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y]->getTypeID()) ){
                        center->setOrientation(1);
                    }
                    
                    
                    // ╗
                    
                    if(TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y+1]->getTypeID()) ){
                        center->setOrientation(3);
                    }
                    if(TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x-1][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y+1]->getTypeID()) ){
                        center->setOrientation(3);
                    }
                    if(TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x-1][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y]->getTypeID()) &&
                       TypeID != (virtMap[x][y-1]->getTypeID())) {
                        center->setOrientation(3);
                    }
                    
                    
                    
                    // ╝
                    
                    if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y-1]->getTypeID()) ){
                        center->setOrientation(5);
                    }
                    if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y-1]->getTypeID()) ){
                        center->setOrientation(5);
                    }
                    if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x-1][y-1]->getTypeID())){
                        center->setOrientation(5);
                    }
                    
                    
                    
                    
                    
                    // ╩
                    
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y-1]->getTypeID()) ){
                        center->setOrientation(9);
                    }
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x+1][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y-1]->getTypeID()) ){
                        center->setOrientation(9);
                    }
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y-1]->getTypeID()) ){
                        center->setOrientation(9);
                    }
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x-1][y-1]->getTypeID()) ){
                        center->setOrientation(9);
                    }
                    
                    
                    
                    
                    // ╣
                    
                    
                    if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x-1][y]->getTypeID()) ){
                        
                        if(TypeID != (virtMap[x-1][y-1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y+1]->getTypeID()) &&
                           TypeID == (virtMap[x+1][y]->getTypeID()) ){
                            center->setOrientation(7);
                        }
                        if(TypeID == (virtMap[x-1][y-1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y+1]->getTypeID()) &&
                           TypeID != (virtMap[x+1][y]->getTypeID()) ){
                            center->setOrientation(7);
                        }
                        if(TypeID != (virtMap[x-1][y-1]->getTypeID()) &&
                           TypeID == (virtMap[x-1][y+1]->getTypeID()) &&
                           TypeID != (virtMap[x+1][y]->getTypeID()) ){
                            center->setOrientation(7);
                        }
                    }
                    
                    
                    
                    
                    // ╦
                    
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y+1]->getTypeID()) ){
                        center->setOrientation(8);
                    }
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y+1]->getTypeID()) ){
                        center->setOrientation(8);
                    }
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x-1][y+1]->getTypeID()) ){
                        center->setOrientation(8);
                    }
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x+1][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y+1]->getTypeID()) ){
                        center->setOrientation(8);
                    }
                    
                    
                    // ╡
                    if(TypeID != (virtMap[x][y-1])->getTypeID() &&
                       TypeID != (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y]->getTypeID()) ){
                        center->setOrientation(12);
                    }
                    
                    
                    
                }
                
                if(TypeID == (virtMap[x+1][y]->getTypeID()) ){
                    
                    // ╚
                    if(TypeID == (virtMap[x][y-1])->getTypeID() &&
                       TypeID == (virtMap[x+1][y]->getTypeID()) ){
                        
                        if(TypeID == (virtMap[x][y+1]->getTypeID()) &&
                           TypeID == (virtMap[x-1][y]->getTypeID()) &&
                           TypeID != (virtMap[x+1][y-1]->getTypeID())
                           ){
                            center->setOrientation(4);
                        }
                        if(TypeID != (virtMap[x][y+1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y]->getTypeID()) &&
                           TypeID != (virtMap[x+1][y-1]->getTypeID()) ){
                            center->setOrientation(4);
                        }
                        if(TypeID != (virtMap[x][y+1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y]->getTypeID()) &&
                           TypeID == (virtMap[x+1][y-1]->getTypeID()) ){
                            center->setOrientation(4);
                        }
                        
                        
                    }
                    
                    
                    // ║ for right side walls
                    
                    if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y]->getTypeID()) ){
                        center->setOrientation(1);
                    }
                    
                    
                    // ╔
                    
                    if(TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x+1][y]->getTypeID()) ){
                        
                        if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                           TypeID == (virtMap[x-1][y]->getTypeID()) &&
                           TypeID != (virtMap[x+1][y+1]->getTypeID()) ){
                            center->setOrientation(2);
                            
                        }
                        if(TypeID != (virtMap[x][y-1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y]->getTypeID()) &&
                           TypeID == (virtMap[x+1][y+1]->getTypeID()) ){
                            center->setOrientation(2);
                            
                        }
                        if(TypeID != (virtMap[x+1][y+1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y]->getTypeID()) &&
                           TypeID != (virtMap[x][y-1]->getTypeID()) ){
                            center->setOrientation(2);
                        }
                    }
                    
                    
                    
                    // ╞
                    
                    if(TypeID != (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y]->getTypeID())  ){
                        center->setOrientation(11);
                    }
                    
                    
                    // ╠
                    
                    if(TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID == (virtMap[x+1][y]->getTypeID()) ){
                        if(TypeID != (virtMap[x+1][y-1]->getTypeID()) &&
                           TypeID != (virtMap[x+1][y+1]->getTypeID()) &&
                           TypeID == (virtMap[x-1][y]->getTypeID()) ){
                            center->setOrientation(6);
                        }
                        if(TypeID == (virtMap[x+1][y-1]->getTypeID()) &&
                           TypeID != (virtMap[x+1][y+1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y]->getTypeID()) ){
                            center->setOrientation(6);
                        }
                        if(TypeID != (virtMap[x+1][y-1]->getTypeID()) &&
                           TypeID == (virtMap[x+1][y+1]->getTypeID()) &&
                           TypeID != (virtMap[x-1][y]->getTypeID()) ){
                            center->setOrientation(6);
                        }
                    }
                    
                    
                    
                    // ╬
                    
                    if(TypeID == (virtMap[x+1][y]->getTypeID()) &&
                       TypeID == (virtMap[x][y-1]->getTypeID()) &&
                       TypeID == (virtMap[x][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x+1][y+1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y-1]->getTypeID()) &&
                       TypeID != (virtMap[x-1][y+1]->getTypeID()) ){
                        center->setOrientation(10);
                    }
                }
            }
            
            
            
            if(TypeID == (virtMap[x][y-1]->getTypeID())){
                
                
                // ║ for walls with nothing to the left or right of them.
                
                if(TypeID == (virtMap[x][y+1]->getTypeID()) &&
                   TypeID != (virtMap[x-1][y]->getTypeID()) &&
                   TypeID != (virtMap[x+1][y]->getTypeID())  ){
                    center->setOrientation(1);
                }
                
                // ╨
                
                if(TypeID != (virtMap[x][y+1]->getTypeID()) &&
                   TypeID != (virtMap[x+1][y]->getTypeID()) &&
                   TypeID != (virtMap[x-1][y]->getTypeID()) &&
                   TypeID == (virtMap[x][y-1]->getTypeID()) ){
                    center->setOrientation(14);
                }
            }
            
            
            // ╥ - Finally our last character
            if(TypeID == (virtMap[x][y+1]->getTypeID())){
                if(TypeID != (virtMap[x][y-1]->getTypeID()) &&
                   TypeID != (virtMap[x+1][y]->getTypeID()) &&
                   TypeID != (virtMap[x-1][y]->getTypeID()) ){
                    center->setOrientation(13);
                }
            }
        }
    }
}



void TileMap::orientWalls(int x1, int y1, int x2, int y2){
    
    
}

void TileMap::importRoom(Room *source){
	rooms[numRooms] = source;
	numRooms++;
}

void TileMap::importAllRooms(TileMap *source){
	TileMap *tmp = source;
    
	if (tmp->numRooms != 0){
		for( x = 0; x < tmp->numRooms; x++){
			importRoom(tmp->rooms[x]);
		}
	}
}

void TileMap::clearRooms(){
	for(x = 0; x < numRooms; x++){
		clearRoom(x);
	}
}

void TileMap::clearRoom(int x){
	delete rooms[x];
	numRooms--;
}

void TileMap::importHall(Hall *source){
	halls[numHalls] = source;
	numHalls++;
}

void TileMap::importAllHalls(TileMap *source){
	TileMap *tmp = source;
    
	if (tmp->numHalls != 0){
		for(  x = 0; x < tmp->numHalls; x++){
			importHall(tmp->halls[x]);
		}
	}
}

void TileMap::clearHall(int x){
	delete halls[x];
	numHalls--;
}

void TileMap::clearHalls(){
	for ( x=0; x < numHalls; x++)
		clearHall(x);
}

void TileMap::copyVirtMap(TileMap *source){
    
	TileMap *tmp = source;
    
	for( x = 0; x < MAP_WIDTH; x++){
		for( y = 0; y < MAP_HEIGHT; y++){
			virtMap[x][y] = tmp->virtMap[x][y];
		}
	}
}


void TileMap::importMap(TileMap *source){
    
	TileMap *tmp = source;
    
	refreshMap();
	clearRooms();
	clearHalls();
    
	importAllRooms(tmp);
	importAllHalls(tmp);
    
	drawAllRooms();
	drawAllHalls();
    orientWalls();
    
}



