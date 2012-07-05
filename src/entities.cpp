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

Entity::Entity(char* p, TCODColor foreinit, int startX, int startY){
	init_entity( p, foreinit, startX, startY);
}

void Entity::init_entity(char* p, TCODColor foreinit, int startX, int startY){
	posX = startX;
	posY = startY;
	symbol = p;
	fore = foreinit;
}


void Entity::move(int dx, int dy){
	
	posX = dx;
	posY = dy;

}

void Entity::clean(TCODConsole *dest){
	TCODConsole *screen = dest;
	screen->print(posX, posY, " ");
}

void Entity::draw(TCODConsole *dest){
	TCODConsole *screen = dest;
	screen->setDefaultForeground(fore);
	screen->print(posX, posY, symbol);

}

