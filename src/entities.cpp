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

Entity::Entity(char* p, int set_color){
	init_entity( p, set_color);
}

void Entity::init_entity(char* p, int set_color){
	symbol = p;
	color = set_color;
	X = 0;
	Y = 0;
	
	initialized = false;


}



bool Entity::move(Map *destination, int dx, int dy){

	Map *map = destination;
	if ( (map->virtMap[(dx + X)][(dy + Y)]->blocked))
	       return false;
	else{
			X += dx;
			Y += dy;
			return true;
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



void Entity::move_self(int dx, int dy){

	move(world, dx, dy);


};









