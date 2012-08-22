/*
 * =====================================================================================
 *
 *       Filename:  Tiles.cpp
 *
 *    Description:  This object defines the behavior of all Tiles, ie
 *                  Necessary functions in order for our world to operate.
 *
 *        Version:  1.0
 *        Created:  07/03/2012 07:51:39 AM
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

using namespace std;





Tile::Tile(bool blked){
	init_Tile(blked);
}

void Tile::init_Tile(bool blked){
    
    blocked = blked;
	visible = false;
	explored = false;
	occupied = false;
    
    
    symbol = (wchar_t *)L"\uFFF0";
    
    TypeID = 0;
    SubTypeID = 0;
    
	H = 0.0;
	S = 0.0;
	V = 0.0;
	HD = 0.0;
	SD = 0.0;
	VD = 0.0;
	R = 0;
	G = 0;
	B = 0;
	RD = 0;
	GD = 0;
	BD = 0;
    
    
    
    
	if(blked){
		block_sight = true;
		explored = false;
	}
	else{
		block_sight = false;
		visible = true;
	}
}

bool Tile::isSightBlocked(){
	return block_sight;
}

bool Tile::isBlocked(){
	return blocked;
}

bool Tile::isVisible(){
	return visible;
}

bool Tile::isExplored(){
	return explored;
}

void Tile::setSymbol(wchar_t *ch){
    symbol = ch;
}

wchar_t *Tile::getSymbol(){
    
	return symbol;
    
}

void Tile::setTypeID(int i){
    TypeID = i;
}

void Tile::setSubTypeID(int i){
    SubTypeID = i;
}

unsigned int Tile::getTypeID(){
    return TypeID;
}

unsigned int Tile::getSubTypeID(){
    return SubTypeID;
}

//Tile *Tile::getPtr(){
//   return this;
//}





Wall::Wall(bool blked){
    
	block_sight = blked;
	blocked = blked;
    needsOrientation = true;
    
	H = 208.0;
	S = 0.0;
	V = 0.4;
    
	HD = 30.0;
	SD = 0.0;
	VD = 0.1;
    
    setTypeID(1);
    
    // This is godawful, but it's only a short term solution
    // For testing things out.
    
    orient[0] = (wchar_t *)L"\u2550";
    orient[1] = (wchar_t *)L"\u2551";
    orient[2] = (wchar_t *)L"\u2554";
    orient[3] = (wchar_t *)L"\u2557";
    orient[4] = (wchar_t *)L"\u255A";
    orient[5] = (wchar_t *)L"\u255D";
    orient[6] = (wchar_t *)L"\u2560";
    orient[7] = (wchar_t *)L"\u2563";
    orient[8] = (wchar_t *)L"\u2566";
    orient[9] = (wchar_t *)L"\u2569";
    orient[10] = (wchar_t *)L"\u256C";
    orient[11] = (wchar_t *)L"\u255E";
    orient[12] = (wchar_t *)L"\u2561";
    orient[13] = (wchar_t *)L"\u2565";
    orient[14] = (wchar_t *)L"\u2568";
    orient[15] = (wchar_t *)L"\u2B1C";
    
    
    
    setSymbol(orient[15]);
    
    
}

void Wall::setOrientation(int i){
    
    setSymbol(orient[i]);
    
}










Floor::Floor(bool blked){
    
	block_sight = blked;
	blocked = blked;
    setTypeID(2);
    
    
	H = 30.4;
	S = 1.0;
	V = 0.3;
    
	HD = 30.4;
	SD = 1.0;
	VD = 0.1;
    
    setSymbol((wchar_t *)L"\u2059");
    
    
    
}

void Floor::setOrientation(int i){
    ;
}





Rect::Rect(int x, int y, int w, int h){
	initRect(x, y, w, h);
}

void Rect::initRect(int x, int y, int w, int h){
    
    
	x1 = x;
	y1 = y;
	x2 = x + w;
	y2 = y + h;
    
	cX = (x1+x2)/2;
	cY = (y1+y2)/2;
}





Room::Room(int x, int y, int w, int h){
	initRoom(x, y, w, h);
}

void Room::initRoom(int x, int y, int w, int h){
    
	Rect *dim = new Rect(x, y, w, h);
    
	x1 = dim->x1;
	x2 = dim->x2;
	y1 = dim->y1;
	y2 = dim->y2;
    
	cX = dim->cX;
	cY = dim->cY;
	delete (dim);
}

bool Room::doesContainPoint(int x, int y){
    
	if ( x > x1 && x < x2 && y > y1 && y < y2)
		return true;
	else
		return false;
}

bool Room::doesIntersect(Room *other){
    
	Room *othr = other;
    
	if ((x1 <= othr->x2) && (x2 >= othr->x1) && (y1 <= othr->y2) && (y2 >= othr->y1))
		return true;
	else
		return false;
}





Hall::Hall(int x, int z, int i, int dir){
	initHall( x, z, i, dir);
}

void Hall::initHall(int x, int z, int i, int d){
    
	x1 = min(x, z);
	x2 = max(x, z);
	y = i;
    
	dir = d;
    
}




