/*
 * =====================================================================================
 *
 *       Filename:  Entities.cpp
 *
 *    Description:  This object defines the behavior of our "Entities", ie
 *                  The necessary functions for an entity to exist on the "Map"
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


void Entity::init_entity(wchar_t *p){

	symbol = p;
	X = 0;
	Y = 0;

	H = 0;
	S = 0;
	V = 0;

	R = 0;
	G = 0;
	B = 0;




	initialized = false;

	int x, y;
	for ( x=0; x < MAP_WIDTH; x++){
		for ( y=0; y < MAP_HEIGHT; y++){
			fov[x][y] = false;
		}
	}
}

bool Entity::move(TileMap *destination, int dx, int dy){

	TileMap *map = destination;
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
}

int Entity::posY(){
	return Y;
}

void Entity::init_in_world(TileMap *destination){

	TileMap *world = destination;
	initialized = true;


}

wchar_t *Entity::getSymbol(){

	return symbol;

}

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

	init_entity( L"\u263A" );

}

Player::Player(){

	init_entity( L"\u263A" );
        H = 0.0;
	S = 0.0;
	V = 1.0;

}

Goblin::Goblin(){

	init_entity( L"\uFB7F" );
	H = 107.0;
	S = 1.0;
	V = 0.40;

}

