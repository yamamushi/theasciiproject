/*
 * =====================================================================================
 *
 *       Filename:  RenderMap.cpp
 *
 *    Description:  This object stores the Symbol and Color information
 *              for use in our Graphics Rendering library.
 *
 *        Version:  1.0
 *        Created:  07/19/2012
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


RenderMap::RenderMap(TileMap *tiles, EntityMap *entities){

    initRenderMap(tiles, entities);

}

void RenderMap::initRenderMap(TileMap* tiles, EntityMap* entities){

    int x, y;

    for (x = 0; x < MAP_WIDTH; x++){
        for (y = 0; y < MAP_HEIGHT; y++){
            if (entities->checkOccupied(x, y)){

                scan = entities->outputLastEntity(x, y);
                Rmap[x][y]->symbol = scan->getSymbol();
                Rmap[x][y]->H = scan->H;
                Rmap[x][y]->S = scan->S;
                Rmap[x][y]->V = scan->V;

            }
            else {

            Rmap[x][y]->symbol = tiles->virtMap[x][y]->getSymbol();
            Rmap[x][y]->H = tiles->virtMap[x][y]->H;
            Rmap[x][y]->S = tiles->virtMap[x][y]->S;
            Rmap[x][y]->V = tiles->virtMap[x][y]->V;
            
            }
        }
    }
}

wchar_t *RenderMap::getSymbol(int x, int y){

    return Rmap[x][y]->symbol;

}

