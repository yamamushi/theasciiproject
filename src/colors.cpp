/*
 * =====================================================================================
 *
 *       Filename:  colors.cpp
 *
 *    Description:  Our coloring functions
 *
 *        Version:  1.0
 *        Created:  07/03/201
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yamamushi (Jon Rumion)
 *   Organization:  The ASCII Project
 *
 *        License:  GPLv3
 *
 *        Copyright 2012 Jonathan Rumion
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

colorTable::colorTable(bool init){
	initColors(init);
}

void colorTable::initColors(bool init){
	if(init){
		TCODColor dark_wall_init(0, 0, 100);
		dark_wall = dark_wall_init;
	 	TCODColor dark_ground_init(50, 50, 150);
		dark_ground = dark_ground_init;
	}
}

void colorTable::setColor(Entity *target, TCODColor foreinit){
	Entity *tgt = target;
	tgt->fore = foreinit;
}


