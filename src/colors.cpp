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




colorTableTCOD::colorTableTCOD() {
	initColorTable();
}


void colorTableTCOD::initColorTable(){

	TCODColor dark_wall(0, 0, 100);
	colorTable[DARK_WALL] = &dark_wall;
	TCODColor dark_ground(50, 50, 150);
	colorTable[DARK_GROUND] = &dark_ground;
	TCODColor light_wall(130, 110, 50);
	colorTable[LIGHT_WALL] = &light_wall; 
	TCODColor light_ground(200, 180, 50);
	colorTable[LIGHT_GROUND] = &light_ground;

}



TCODColor colorTableTCOD::color(int i){

	return *colorTable[i];
}






