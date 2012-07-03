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
 * =====================================================================================
 */
#include "libtcod.hpp"
#include "map.h"


Tile::Tile(bool blked){
	init_Tile(blked);
}

void Tile::init_Tile(bool blked){
	blocked = blked;
	if(blked)
		block_sight = true;
}

