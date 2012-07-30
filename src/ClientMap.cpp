/*
 * =====================================================================================
 *
 *       Filename:  Client.cpp
 *
 *    Description:  This object stores the Symbol and Color information
 *              for use in our Client-Side Graphics Rendering library.
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


ClientMap::ClientMap(){
    
    initClientMap();
    
}

void ClientMap::initClientMap(){
    
    clearMap();
    
}

void ClientMap::clearMap(){
    
    int x, y;
    
    for (x = 0; x < MAP_WIDTH; x++){
        for (y = 0; y < MAP_HEIGHT; y++){
            
            cMap[x][y] = new render_t;
            
            cMap[x][y]->symbol = (wchar_t *)L"\uFFFF";
            cMap[x][y]->x = x;
            cMap[x][y]->y = y;
            cMap[x][y]->H = 0.0;
            cMap[x][y]->HD = 0.0;
            cMap[x][y]->S = 0.0;
            cMap[x][y]->SD = 0.0;
            cMap[x][y]->V = 0.0;
            cMap[x][y]->VD = 0.0;
            cMap[x][y]->explored = false;
            cMap[x][y]->occupied = false;
            cMap[x][y]->visible = false;
            
        }
    }
}

void ClientMap::deleteMap(){
    
    int x, y;
    
    for (x = 0; x < MAP_WIDTH; x++){
        for (y = 0; y < MAP_HEIGHT; y++){
            
            delete cMap[x][y];
        }
    }
    
}

void ClientMap::refreshSquare(int x, int y){
    
    removeSquare(x, y);
    createSquare(x, y);
    
}

void ClientMap::removeSquare(int x, int y){
    
    free(cMap[x][y]->symbol);
    delete cMap[x][y];
    
}

void ClientMap::createSquare(int x, int y){
    
    cMap[x][y] = new render_t;
    
}


void ClientMap::cleanMap()
{

    int x, y;
    for (x = 0; x < MAP_WIDTH; x++){
        for (y = 0; y < MAP_HEIGHT; y++){
            cMap[x][y]->occupied = false;
            cMap[x][y]->visible = false;
        }
    }
    
}


void ClientMap::importSquare(int x, int y, render_t *square){
    
    cMap[x][y] = square;
    
}

render_t *ClientMap::exportSquare(int x, int y){
    
    return cMap[x][y];
    
}

wchar_t *ClientMap::getSymbol(int x, int y){
    
    return cMap[x][y]->symbol;
    
}

float ClientMap::returnH(int x, int y){
    
    return cMap[x][y]->H;
    
}

float ClientMap::returnHD(int x, int y){
    
    return cMap[x][y]->HD;
    
}

float ClientMap::returnS(int x, int y){
    
    return cMap[x][y]->S;
    
}

float ClientMap::returnSD(int x, int y){
    
    return cMap[x][y]->SD;
    
}

float ClientMap::returnV(int x, int y){
    
    return cMap[x][y]->V;
    
}

float ClientMap::returnVD(int x, int y){
    
    return cMap[x][y]->VD;
    
}

bool ClientMap::returnExplored(int x, int y){
    
    return cMap[x][y]->explored;
    
}

bool ClientMap::returnOccupied(int x, int y){
    
    return cMap[x][y]->occupied;
    
}

bool ClientMap::returnVisible(int x, int y){
    
    return cMap[x][y]->visible;
    
}