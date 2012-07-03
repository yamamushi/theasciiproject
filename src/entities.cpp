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
 * =====================================================================================
 */
#include "libtcod.hpp"
#include "entities.h"

entity::entity(int x, int y, char* p, TCODColor foreinit){
	init_entity( x, y, p, foreinit);
}

void entity::init_entity(int x, int y, char* p, TCODColor foreinit){
	posX = x;
	posY = y;
	symbol = p;
	fore = foreinit;
}

void entity::move(int dx, int dy){
	posX = dx;
	posY = dy;
}

void entity::clean(TCODConsole *dest){
	TCODConsole *screen = dest;
	screen->print(posX, posY, " ");
}

void entity::draw(TCODConsole *dest){
	TCODConsole *screen = dest;
	screen->setDefaultForeground(fore);
	screen->print(posX, posY, symbol);

}

