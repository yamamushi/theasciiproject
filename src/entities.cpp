/*
 * =====================================================================================
 *
 *       Filename:  entities.cpp
 *
 *    Description:  Our entity objects - Subject to change
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:41:29 AM
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


void Entity::init_entity(char* p, int set_color){
	symbol = p;
	color = set_color;
	X = 0;
	Y = 0;
	
	initialized = false;


}



bool Entity::move(Map *destination, int dx, int dy){

	Map *map = destination;
	if (initialized){
		if ( (map->virtMap[(dx + X)][(dy + Y)]->blocked))
		       return false;
		else{
			X += dx;
			Y += dy;
			return true;
		}
	}
	else {
		return false;
	}

}

int Entity::posX(){
	return X;
};

int Entity::posY(){
	return Y;
};



void Entity::init_in_world(Map *destination){

	Map *world = destination;
	initialized = true;

};



int Entity::getColor(){

	return color;

};




char* Entity::getSymbol(){

	return symbol;

};


bool Entity::isInitialized(){

	return initialized;

}








void Entity::move_self(int dx, int dy){

	move(world, dx, dy);


};



void Entity::setEntityMap(EntityMap *map){

	EntityMap *entMap = map;

};









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



EntityMap::EntityMap(int x, int y){

	initEntityMap(x, y);

}




void EntityMap::initEntityMap(int x, int y){

	width = x;
	height = y;
	

}


void EntityMap::addToMap(Entity *entity){

	Entity *src = entity;
	int x, y;
	x = src->posX();
	y = src->posY();
	pos[x][y].push_back(src);


}



void EntityMap::createEntity(int type){

	Entity *newEntity;

	switch (type) {
		
		case MONSTER:
			newEntity = new Monster();
		case PLAYER:
			newEntity = new Player();

	}
	
	addToMap(newEntity);

}


void EntityMap::initAllEnts(Map *destination){


	Map *contextMap = destination;

	int x, y, z;
	
	for ( x = 0; x < width; x++){
		for ( y = 0; y < height; y++){
			if (!(pos[x][y].empty())){
				for ( z = 0; z < pos[x][y].size(); z++){
					pos[x][y].at(z)->init_in_world(contextMap);
				}
			}
		}
	}
}



/*
 *
 *
 *		Entities
 *
 *	Now we start listing some entity types
 *
 *	Though how this works will likely change in the
 *	future.
 *
 *
 *
 */















Monster::Monster(){

	init_entity( "@", RED );

}



void Monster::initMonster(int x, int y){

	int z, i;
	i = x;
	z = y;

}




Player::Player(){

	init_entity( "@", WHITE);

}



















