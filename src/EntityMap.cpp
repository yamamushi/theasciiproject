/*
 * =====================================================================================
 *
 *       Filename:  EntityMap.cpp
 *
 *    Description:  EntityMap is an object which stores the location of all
 *                  Entities on the "Map".
 *
 *        Version:  1.0
 *        Created:  07/11/2012
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





/*
 *
 * 		Here begins our EntityMap object.
 *
 * 	The purpose of this object is to store a
 * 	static-sized 2-dimensional array of vectors.
 *
 * 	Each vector is a list of Entities, thus
 * 	A seemingly "infinite" amount of entities can
 * 	exist in one space of a map at one time.
 *
 * 	This Object will thus return the color map
 * 	(which essentially allows the graphics rendering
 * 	engine to render entities without doing
 * 	much thought on it's own).
 *
 *	This Object will also allow each individual entity
 *	to gather information about other entities in
 *	its own context.
 *
 *
 */



EntityMap::EntityMap(int x, int y, TileMap *map, FovLib *FOVLib){

	initEntityMap(x, y, map, FOVLib);

}

void EntityMap::initEntityMap(int x, int y, TileMap *map, FovLib *FOVLib){

	width = x;
	height = y;

        contextMap = map;
        fovLib = FOVLib;


}

void EntityMap::addToMap(Entity *entity){

	Entity *src = entity;
	int x, y;

	x = src->posX();
	y = src->posY();
	pos[x][y].push_back(src);
        src->init_in_world(fovLib);
        src->setEntityMap(this);

}

void EntityMap::createEntity(int type){

	Entity *newEntity;

	switch (type) {

		case MONSTER:
			newEntity = new Monster();
            addToMap(newEntity);
		case PLAYER:
			newEntity = new Player();
            addToMap(newEntity);
	}

}

void EntityMap::initAllEnts(){


	int x, y, z;

	for ( x = 0; x < width; x++){
		for ( y = 0; y < height; y++){
			if (!(pos[x][y].empty())){
				for ( z = 0; z < pos[x][y].size(); z++){
					pos[x][y].at(z)->init_in_world(fovLib);
                                        pos[x][y].at(z)->setEntityMap(this);
				}
			}
		}
	}
}

void EntityMap::refreshEntityMap(){

	int x, y, z;

	for ( x = 0; x < width; x++){
		for ( y = 0; y < height; y++){
			if( !(pos[x][y].empty()) ){
				for ( z = 0; z < pos[x][y].size(); z++){
					// check each entity in this vector
					// move entity to new vector
					// coordinates at x and y

					// First we check to see if this entities
					// coordinates differ from our own:
					Entity *cur = pos[x][y].at(z);

					if ( (x != (cur->posX())) || (y != (cur->posY())) ){
						// now we do some magic
						int newX = cur->posX();
						int newY = cur->posY();

						pos[newX][newY].push_back(cur);
						pos[x][y].erase(pos[x][y].begin()+z);
					}
				}
			}
		}
	}

}

bool EntityMap::checkOccupied(int x, int y){

	if ( !(pos[x][y].empty()) ){
		return true;
	}
	else
		return false;
}

Entity * EntityMap::outputLastEntity(int x, int y){

	//if ( !(pos[x][y].empty()) ){
		Entity *current = pos[x][y].back();
		return current;
	//}
}

void EntityMap::refreshFovFor(Entity *tgt){

    fovLib->refreshFov(tgt);

}

