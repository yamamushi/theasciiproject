/*
 * =====================================================================================
 *
 *       Filename:  Entities.cpp
 *
 *    Description:  This object defines the behavior of our "Entities", ie
 *                  The necessary functions for an entity to exist on the "Map"
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

#include "Headers.h"

// Temporary location for these variables, they will be moved elsewhere
// When DB library code is integrated (soon-ish).

unsigned int UIDList = 0;

void Entity::init_entity(wchar_t *p)
{
    
    
    symbol = p;
    X = 0;
    Y = 0;
    
    H = 0;
    S = 0;
    V = 0;
    
    R = 0;
    G = 0;
    B = 0;
    
    TypeID = 0;
    SubTypeID = 0;
    UID = UIDList + 1;
    UIDList++;
    
    
    initialized = false;
    clientActive = false;
    
    int x, y;
    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            fov[x][y] = false;
        }
    }
}


void Entity::setEntName(std::string entName_)
{
    
    entName = entName_;
    
}


std::string Entity::getEntName()
{
    
    return entName;
    
}

void Entity::setPos(int x, int y)
{
    X = x;
    Y = y;
    
}


bool Entity::move(int dx, int dy)
{
    
    if(dx+X > 0 && dx+X < MAP_WIDTH && dy+Y > 0 && dy+Y < MAP_HEIGHT)
    {
        if (initialized) {
            if ((world->virtMap[(dx + X)][(dy + Y)]->blocked) || entMap->checkOccupied(dx+X, dy+Y)){
                entMap->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return false;
            }
            else {
                X += dx;
                Y += dy;
                
                entMap->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    
}


bool Entity::digTile(int dx, int dy)
{
    
    if(dx+X > 0 && dx+X < MAP_WIDTH && dy+Y > 0 && dy+Y < MAP_HEIGHT)
    {
        if (initialized) {
            if ((world->virtMap[(dx + X)][(dy + Y)]->blocked)){
                entMap->contextMap->removeTile(dx + X, dy + Y);
                //entMap->refreshTileMap();
                entMap->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return true;
            }
            else {
                
                entMap->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return false;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else if(dx+X > 0 && dx+X >= MAP_WIDTH && dy+Y >= 0 && dy+Y < MAP_HEIGHT)
    {
        if (initialized) {
            if ((wMap->getNextEntMap(this, 6)->contextMap->virtMap[1][(dy + Y)]->blocked)){
                
                wMap->getNextEntMap(this, 6)->contextMap->removeTile(1, dy+Y);
                wMap->getNextEntMap(this, 6)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return true;
            }
            else {
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return false;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else if(dx+X <= 0 && dx+X < MAP_WIDTH && dy+Y >= 0 && dy+Y < MAP_HEIGHT)
    {
        if (initialized) {
            if ((wMap->getNextEntMap(this, 4)->contextMap->virtMap[MAP_WIDTH-1][(dy + Y)]->blocked)){
                wMap->getNextEntMap(this, 4)->contextMap->removeTile(MAP_WIDTH-1, dy+Y);
                wMap->getNextEntMap(this, 4)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return true;
            }
            else {
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return false;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else if(dx+X >= 0 && dx+X < MAP_WIDTH && dy+Y > 0 && dy+Y >= MAP_HEIGHT)
    {
        cout << "test 1" << endl;
        if (initialized) {
            if ((wMap->getNextEntMap(this, 2)->contextMap->virtMap[dx+X][(1)]->blocked)){
                wMap->getNextEntMap(this, 2)->contextMap->removeTile(dx+X,1);
                wMap->getNextEntMap(this, 2)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return true;
            }
            else {
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return false;
            }
        }
        else
        {
            return false;
        }
        
    }
    else if(dx+X >= 0 && dx+X < MAP_WIDTH && dy+Y <= 0 && dy+Y < MAP_HEIGHT)
    {
        cout << "test 2" << endl;;
        if (initialized) {
            if ((wMap->getNextEntMap(this, 8)->contextMap->virtMap[dx+X][(MAP_HEIGHT-1)]->blocked)){
                wMap->getNextEntMap(this, 8)->contextMap->removeTile(dx+X, MAP_HEIGHT-1);
                wMap->getNextEntMap(this, 8)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return true;
            }
            else {
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return false;
            }
        }
        else
        {
            return false;
        }
        
        
    }

    else
    {
        return false;
    }
}



bool Entity::placeTile(int dx, int dy)
{
    
    if(dx+X > 0 && dx+X < MAP_WIDTH && dy+Y > 0 && dy+Y < MAP_HEIGHT)
    {
        if (initialized) {
            if ((world->virtMap[(dx + X)][(dy + Y)]->blocked) || entMap->checkOccupied(dx+X, dy+Y)){
                entMap->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return false;
            }
            else {
                
                entMap->contextMap->placeTile(dx + X, dy + Y);
                //entMap->refreshTileMap();
                entMap->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return true;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else if(dx+X > 0 && dx+X >= MAP_WIDTH && dy+Y >= 0 && dy+Y < MAP_HEIGHT)
    {
        if (initialized) {
            if ((wMap->getNextEntMap(this, 6)->contextMap->virtMap[1][(dy + Y)]->blocked) || wMap->getNextEntMap(this, 6)->checkOccupied(1, dy+Y)){
                wMap->getNextEntMap(this, 6)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return false;
            }
            else {
                
                wMap->getNextEntMap(this, 6)->contextMap->placeTile(1, dy + Y);
                //entMap->refreshTileMap();
                wMap->getNextEntMap(this, 6)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return true;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else if(dx+X <= 0 && dx+X < MAP_WIDTH && dy+Y >= 0 && dy+Y < MAP_HEIGHT)
    {
        if (initialized) {
            if ((wMap->getNextEntMap(this, 4)->contextMap->virtMap[MAP_WIDTH-1][(dy + Y)]->blocked) || wMap->getNextEntMap(this, 4)->checkOccupied(MAP_WIDTH-1, dy+Y)){
                wMap->getNextEntMap(this, 4)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return false;
            }
            else {
                
                wMap->getNextEntMap(this, 4)->contextMap->placeTile(MAP_WIDTH-1, dy + Y);
                //entMap->refreshTileMap();
                wMap->getNextEntMap(this, 4)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return true;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else if(dx+X >= 0 && dx+X < MAP_WIDTH && dy+Y > 0 && dy+Y >= MAP_HEIGHT)
    {
        if (initialized) {
            if ((wMap->getNextEntMap(this, 2)->contextMap->virtMap[dx+X][(1)]->blocked) || wMap->getNextEntMap(this, 2)->checkOccupied(dx+X, 1)){
                wMap->getNextEntMap(this, 2)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return false;
            }
            else {
                
                wMap->getNextEntMap(this, 2)->contextMap->placeTile(dx+X, 1);
                //entMap->refreshTileMap();
                wMap->getNextEntMap(this, 2)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return true;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else if(dx+X >= 0 && dx+X < MAP_WIDTH && dy+Y <= 0 && dy+Y < MAP_HEIGHT)
    {
        cout << "checking north" << endl;
        if (initialized) {
            if ((wMap->getNextEntMap(this, 8)->contextMap->virtMap[X][(MAP_HEIGHT-1)]->blocked) || wMap->getNextEntMap(this, 8)->checkOccupied(dx+X, MAP_HEIGHT-1)){
                wMap->getNextEntMap(this, 8)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                return false;
            }
            else {
                
                wMap->getNextEntMap(this, 8)->contextMap->placeTile(dx+X, MAP_HEIGHT-1);
                //entMap->refreshTileMap();
                wMap->getNextEntMap(this, 8)->refreshEntityMap();
                
                if (clientActive) {
                    
                    clientFovSync();
                }
                
                
                return true;
            }
        }
        else
        {
            return false;
        }
        
        
    }
    else
    {
        return false;
    }
}


void Entity::setGlobal(WorldMap *WMap)
{
    
    if(WMap != nullptr)
        wMap = WMap;

    
}



void Entity::setWorldPosition(int x, int y, int z)
{
    
    wX = x;
    wY = y;
    wZ = z;
    
    
}

void Entity::clientFovSync(){
    
    
    //refreshFov(10);
    
    
    int pX, pY;
    pX = X;
    pY = Y;
    
    int cX, cY;
    cX = MAP_WIDTH/2;
    cY= MAP_HEIGHT/2;
    
    
    int offset = cY-4;
    
    int x = pX-offset;
    for(int iX = cX-offset; iX < cX+offset; iX++ )
    {
        int y = pY-offset;
        for(int iY = cY-offset; iY < cY+offset; iY++ )
        {
            cMap->cMap[iX][iY]->explored = true;
            cMap->cMap[iX][iY]->visible = true;
            
            if(y > 0 && y < MAP_HEIGHT && x > 0 && x < MAP_WIDTH)
                
            {
                
                cMap->cMap[iX][iY]->symbol = rMap->getSymbol(x, y);
                cMap->cMap[iX][iY]->H = rMap->returnH(x, y);
                cMap->cMap[iX][iY]->HD = rMap->returnHD(x, y);
                cMap->cMap[iX][iY]->S = rMap->returnS(x, y);
                cMap->cMap[iX][iY]->SD = rMap->returnSD(x, y);
                cMap->cMap[iX][iY]->V = rMap->returnV(x, y);
                cMap->cMap[iX][iY]->VD = rMap->returnVD(x, y);
                //cMap->cMap[cX][cY]->explored = true;
                
                
              /*  if(fov[x][y] == true)
                {
                    
                    cMap->cMap[iX][iY]->visible = true;
                    //cMap->cMap[iX][iY]->explored = true;
                    
                }
                else
                {
                    cMap->cMap[iX][iY]->visible = false;
                    cMap->cMap[iX][iY]->occupied = false;
                } */
                
                
            }
            
            else if(y > 0 && y > MAP_HEIGHT && x > 0 && x < MAP_WIDTH)    
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 2)->rMap;
                int iy;
                iy = y-MAP_HEIGHT;
                
                cMap->cMap[iX][iY-1]->symbol = trMap->getSymbol(x, iy);
                cMap->cMap[iX][iY-1]->H = trMap->returnH(x, iy);
                cMap->cMap[iX][iY-1]->HD = trMap->returnHD(x, iy);
                cMap->cMap[iX][iY-1]->S = trMap->returnS(x, iy);
                cMap->cMap[iX][iY-1]->SD = trMap->returnSD(x, iy);
                cMap->cMap[iX][iY-1]->V = trMap->returnV(x, iy);
                cMap->cMap[iX][iY-1]->VD = trMap->returnVD(x, iy);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
                
              /*  FovLib *tFov = wMap->getNextEntMap(this, 2)->fovLib;
                tFov->refreshFov(this, x, y);
                
                if(fov[x][y] == true)
                {
                    
                    cMap->cMap[iX][iY]->visible = true;
                    //cMap->cMap[iX][iY]->explored = true;
                    
                }
                else
                {
                    cMap->cMap[iX][iY]->visible = false;
                    cMap->cMap[iX][iY]->occupied = false;
                } */
                
            } 
            
            else if(y < 0 && y < MAP_HEIGHT && x > 0 && x < MAP_WIDTH)
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 8)->rMap;
                int iy;
                iy = MAP_HEIGHT+y;
                
                cMap->cMap[iX][iY+1]->symbol = trMap->getSymbol(x, iy);
                cMap->cMap[iX][iY+1]->H = trMap->returnH(x, iy);
                cMap->cMap[iX][iY+1]->HD = trMap->returnHD(x, iy);
                cMap->cMap[iX][iY+1]->S = trMap->returnS(x, iy);
                cMap->cMap[iX][iY+1]->SD = trMap->returnSD(x, iy);
                cMap->cMap[iX][iY+1]->V = trMap->returnV(x, iy);
                cMap->cMap[iX][iY+1]->VD = trMap->returnVD(x, iy);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
           /*
                FovLib *tFov = wMap->getNextEntMap(this, 8)->fovLib;
                tFov->refreshFov(this, x, y);
                
                if(fov[x][y] == true)
                {
                    
                    cMap->cMap[iX][iY]->visible = true;
                    //cMap->cMap[iX][iY]->explored = true;
                    
                }
                else
                {
                    cMap->cMap[iX][iY]->visible = false;
                    cMap->cMap[iX][iY]->occupied = false;
                }
                */

            }
            
            else if(y > 0 && y < MAP_HEIGHT && x < 0 && x < MAP_WIDTH)
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 4)->rMap;
                int ix;
                ix = MAP_WIDTH+x;
                
                cMap->cMap[iX+1][iY]->symbol = trMap->getSymbol(ix, y);
                cMap->cMap[iX+1][iY]->H = trMap->returnH(ix, y);
                cMap->cMap[iX+1][iY]->HD = trMap->returnHD(ix, y);
                cMap->cMap[iX+1][iY]->S = trMap->returnS(ix, y);
                cMap->cMap[iX+1][iY]->SD = trMap->returnSD(ix, y);
                cMap->cMap[iX+1][iY]->V = trMap->returnV(ix, y);
                cMap->cMap[iX+1][iY]->VD = trMap->returnVD(ix, y);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
                /*
                 FovLib *tFov = wMap->getNextEntMap(this, 8)->fovLib;
                 tFov->refreshFov(this, x, y);
                 
                 if(fov[x][y] == true)
                 {
                 
                 cMap->cMap[iX][iY]->visible = true;
                 //cMap->cMap[iX][iY]->explored = true;
                 
                 }
                 else
                 {
                 cMap->cMap[iX][iY]->visible = false;
                 cMap->cMap[iX][iY]->occupied = false;
                 }
                 */
                
            }

            
            else if(y > 0 && y < MAP_HEIGHT && x > 0 && x > MAP_WIDTH)
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 6)->rMap;
                int ix;
                ix = x-MAP_WIDTH;
                
                cMap->cMap[iX-1][iY]->symbol = trMap->getSymbol(ix, y);
                cMap->cMap[iX-1][iY]->H = trMap->returnH(ix, y);
                cMap->cMap[iX-1][iY]->HD = trMap->returnHD(ix, y);
                cMap->cMap[iX-1][iY]->S = trMap->returnS(ix, y);
                cMap->cMap[iX-1][iY]->SD = trMap->returnSD(ix, y);
                cMap->cMap[iX-1][iY]->V = trMap->returnV(ix, y);
                cMap->cMap[iX-1][iY]->VD = trMap->returnVD(ix, y);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
                
                /*  FovLib *tFov = wMap->getNextEntMap(this, 2)->fovLib;
                 tFov->refreshFov(this, x, y);
                 
                 if(fov[x][y] == true)
                 {
                 
                 cMap->cMap[iX][iY]->visible = true;
                 //cMap->cMap[iX][iY]->explored = true;
                 
                 }
                 else
                 {
                 cMap->cMap[iX][iY]->visible = false;
                 cMap->cMap[iX][iY]->occupied = false;
                 } */
                
            }
            else if(y < 0 && y < MAP_HEIGHT && x > 0 && x > MAP_WIDTH)
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 9)->rMap;
                int ix, iy;
                ix = x-MAP_WIDTH;
                iy = MAP_HEIGHT+y;
                
                cMap->cMap[iX-1][iY+1]->symbol = trMap->getSymbol(ix, iy);
                cMap->cMap[iX-1][iY+1]->H = trMap->returnH(ix, iy);
                cMap->cMap[iX-1][iY+1]->HD = trMap->returnHD(ix, iy);
                cMap->cMap[iX-1][iY+1]->S = trMap->returnS(ix, iy);
                cMap->cMap[iX-1][iY+1]->SD = trMap->returnSD(ix, iy);
                cMap->cMap[iX-1][iY+1]->V = trMap->returnV(ix, iy);
                cMap->cMap[iX-1][iY+1]->VD = trMap->returnVD(ix, iy);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
                

            }
            else if(y > 0 && y > MAP_HEIGHT && x > 0 && x > MAP_WIDTH)
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 3)->rMap;
                int ix, iy;
                ix = x-MAP_WIDTH;
                iy = y-MAP_HEIGHT;
                
                cMap->cMap[iX-1][iY-1]->symbol = trMap->getSymbol(ix, iy);
                cMap->cMap[iX-1][iY-1]->H = trMap->returnH(ix, iy);
                cMap->cMap[iX-1][iY-1]->HD = trMap->returnHD(ix, iy);
                cMap->cMap[iX-1][iY-1]->S = trMap->returnS(ix, iy);
                cMap->cMap[iX-1][iY-1]->SD = trMap->returnSD(ix, iy);
                cMap->cMap[iX-1][iY-1]->V = trMap->returnV(ix, iy);
                cMap->cMap[iX-1][iY-1]->VD = trMap->returnVD(ix, iy);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
                
                
            }
            else if(y < 0 && y < MAP_HEIGHT && x < 0 && x < MAP_WIDTH)
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 7)->rMap;
                int ix, iy;
                ix = MAP_WIDTH+x;
                iy = MAP_HEIGHT+y;
                
                cMap->cMap[iX+1][iY+1]->symbol = trMap->getSymbol(ix, iy);
                cMap->cMap[iX+1][iY+1]->H = trMap->returnH(ix, iy);
                cMap->cMap[iX+1][iY+1]->HD = trMap->returnHD(ix, iy);
                cMap->cMap[iX+1][iY+1]->S = trMap->returnS(ix, iy);
                cMap->cMap[iX+1][iY+1]->SD = trMap->returnSD(ix, iy);
                cMap->cMap[iX+1][iY+1]->V = trMap->returnV(ix, iy);
                cMap->cMap[iX+1][iY+1]->VD = trMap->returnVD(ix, iy);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
                
                
            }
            else if(y > 0 && y > MAP_HEIGHT && x < 0 && x < MAP_WIDTH)
            {
                
                RenderMap *trMap = wMap->getNextEntMap(this, 1)->rMap;
                int ix, iy;
                ix = MAP_WIDTH+x;
                iy = y-MAP_HEIGHT;
                
                cMap->cMap[iX+1][iY-1]->symbol = trMap->getSymbol(ix, iy);
                cMap->cMap[iX+1][iY-1]->H = trMap->returnH(ix, iy);
                cMap->cMap[iX+1][iY-1]->HD = trMap->returnHD(ix, iy);
                cMap->cMap[iX+1][iY-1]->S = trMap->returnS(ix, iy);
                cMap->cMap[iX+1][iY-1]->SD = trMap->returnSD(ix, iy);
                cMap->cMap[iX+1][iY-1]->V = trMap->returnV(ix, iy);
                cMap->cMap[iX+1][iY-1]->VD = trMap->returnVD(ix, iy);
                //cMap->cMap[iX][iY]->visible = true;
                //cMap->cMap[cX][cY]->explored = true;
                
                
            }
            
            
            y++;
        }
        
        
        x++;
    }

    
}

void Entity::refreshFov(int radius)
{
    
    FOV->refreshFov(this, radius);
    
}

int Entity::posX()
{
    return X;
}

int Entity::posY()
{
    return Y;
}

void Entity::init_in_world(FovLib *fovLib)
{
    
    FOV = fovLib;
    initialized = true;
    world = fovLib->getTileMap();
    
    
    
}

wchar_t *Entity::getSymbol()
{
    
    return symbol;
    
}

void Entity::setSymbol(wchar_t *ch)
{
    symbol = ch;
}

void Entity::setTypeID(int i)
{
    TypeID = i;
}

void Entity::setSubTypeID(int i)
{
    SubTypeID = i;
}

bool Entity::isInitialized()
{
    
    return initialized;
    
}

void Entity::associateClient(RenderMap *RMap)
{
    if(cMap != nullptr)
    {
        delete cMap;
    }
    cMap = new ClientMap();
    rMap = RMap;
    clientActive = true;
    
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            fov[x][y] = false;
        }
    }
    
    entMap->refreshEntityMap();
    
    //  clientFovSync();
    //   refreshFov();
}

bool Entity::getAssociated()
{
    
    return clientActive;
    
}

ClientMap *Entity::returnCMap()
{
    
    return cMap;
    
}

void Entity::move_self(int dx, int dy)
{
    
    move(dx, dy);
    
    
};

void Entity::setEntityMap(EntityMap *map)
{
    
    entMap = map;
    entMap->refreshEntityMap();
    
};

/*
 *
 *
 *		Entities
 *
 *	Now we start listing some entity types
 *
 *	Though how this works will likely change in the
 *	future.
 *
 *
 *
 */



Monster::Monster() : Entity((wchar_t *)L"\uFFF7")
{
    
    //Entity((wchar_t *)L"\u263A");
    
}

Player::Player() : Entity((wchar_t *)L"\u263A")
{
    
    // Entity((wchar_t *)L"\u263A");
    H = 0.0;
    S = 0.0;
    V = 1.0;
    
}

Goblin::Goblin() : Entity((wchar_t *)L"\uFFF7")
{
    
    //  Entity((wchar_t *)L"\uFFF7");
    H = 30.0;
    S = 0.58;
    V = 0.40;
    
}

