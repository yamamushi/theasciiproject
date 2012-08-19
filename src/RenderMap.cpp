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


#include "Headers.h"


RenderMap::RenderMap(TileMap *tiles){
    
    initRenderMap(tiles);
    
}

void RenderMap::initRenderMap(TileMap *tiles){
    
    tMap = tiles;
    
}


void RenderMap::initEntMap(EntityMap *entMap)
{
    eMap = entMap;
    refreshMap();
}


void RenderMap::refreshMap(){
    
    int x, y;
    
    for (x = 0; x < MAP_WIDTH; x++){
        for (y = 0; y < MAP_HEIGHT; y++){
            if (!(eMap->checkOccupied(x, y))){
                
                
                rMap[x][y].symbol = tMap->virtMap[x][y]->getSymbol();
                rMap[x][y].H = tMap->virtMap[x][y]->H;
                rMap[x][y].HD = tMap->virtMap[x][y]->HD;
                rMap[x][y].S = tMap->virtMap[x][y]->S;
                rMap[x][y].SD = tMap->virtMap[x][y]->SD;
                rMap[x][y].V = tMap->virtMap[x][y]->V;
                rMap[x][y].VD = tMap->virtMap[x][y]->VD;
                rMap[x][y].explored = tMap->virtMap[x][y]->isExplored();
                rMap[x][y].occupied = false;
                rMap[x][y].visible = tMap->virtMap[x][y]->isVisible();
                
                
            }
            
            else {
                
                scan = eMap->outputLastEntity(x, y);
                
                rMap[x][y].symbol = scan->getSymbol();
                rMap[x][y].H = scan->H;
                rMap[x][y].S = scan->S;
                rMap[x][y].V = scan->V;
                rMap[x][y].explored = tMap->virtMap[x][y]->isExplored();
                rMap[x][y].occupied = true;
                rMap[x][y].visible = tMap->virtMap[x][y]->isVisible();
                
            }
        }
    }
}

render_t RenderMap::exportSquare(int x, int y){
    
    return rMap[x][y];
    
}



wchar_t *RenderMap::getSymbol(int x, int y){
    
    return rMap[x][y].symbol;
    
}

float RenderMap::returnH(int x, int y){
    
    return rMap[x][y].H;
    
}

float RenderMap::returnHD(int x, int y){
    
    return rMap[x][y].HD;
    
}

float RenderMap::returnS(int x, int y){
    
    return rMap[x][y].S;
    
}

float RenderMap::returnSD(int x, int y){
    
    return rMap[x][y].SD;
    
}

float RenderMap::returnV(int x, int y){
    
    return rMap[x][y].V;
    
}

float RenderMap::returnVD(int x, int y){
    
    return rMap[x][y].VD;
    
}

bool RenderMap::returnExplored(int x, int y){
    
    return rMap[x][y].explored;
    
}

bool RenderMap::returnOccupied(int x, int y){
    
    return rMap[x][y].occupied;
    
}

bool RenderMap::returnVisible(int x, int y){
    
    return rMap[x][y].visible;
    
}