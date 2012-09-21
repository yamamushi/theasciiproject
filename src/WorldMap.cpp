/*
 * =====================================================================================
 *
 *       Filename:  WorldMap.cpp
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



#include "WorldMap.h"

#include "Entities.h"
#include "EntityMap.h"
#include "ClientMap.h"
#include "TileMap.h"






void WorldMap::initWorldMap()
{
    
    for(int x = 0; x < wX; x++)
    {
        for(int y = 0; y < wY; y++)
        {
            for(int z = 0; z < wZ; z++)
            {
                
                eMap->at(x).at(y).at(z) = new EntityMap(MAP_WIDTH, MAP_HEIGHT, new TileMap(MAP_WIDTH, MAP_HEIGHT) );
                eMap->at(x).at(y).at(z)->initWorldMap(this, x, y, z);
                if(z > cZ)
                {
                    eMap->at(x).at(y).at(z)->contextMap->airMap();
                    eMap->at(x).at(y).at(z)->refreshRenderMap();
                }
                else if(z < cZ)
                {
                    eMap->at(x).at(y).at(z)->contextMap->fillMap();
                    eMap->at(x).at(y).at(z)->refreshRenderMap();
                }
                else if (z == cZ)
                {
                    eMap->at(x).at(y).at(z)->refreshRenderMap();
                    eMap->at(x).at(y).at(z)->refreshLightMap();
                }
                
            }
        }
    }
        
}



void WorldMap::addEntToCenter(Entity *tgt)
{
    
    tgt->setGlobal(this);
    tgt->setWorldPosition(cX, cY, cZ);
    eMap->at(cX).at(cY).at(cZ)->addToMap(tgt);
    
    
}


void WorldMap::removeEnt(Entity *tgt)
{
    int tX, tY, tZ;
    tX = tgt->wX;
    tY = tgt->wY;
    tZ = tgt->wZ;
    
    eMap->at(tX).at(tY).at(tZ)->removeFromEntMap(tgt);
    
}



void WorldMap::moveEnt(Entity *tgt, int x, int y)
{
    
    bool moved = tgt->move(x, y);
    
    int oldx, oldy, tWX, tWY, tWZ;
    oldx = tgt->posX();
    oldy = tgt->posY();
    
    tWX = tgt->wX;
    tWY = tgt->wY;
    tWZ = tgt->wZ;
    
    
    
    
    if(!moved && oldx+x <= 0)
    {
        if(tWX == 0)
            tWX = wX;
        if(!eMap->at(tWX-1).at(tWY).at(tWZ)->contextMap->virtMap[MAP_WIDTH-1][oldy]->blocked && eMap->at(tWX-1).at(tWY).at(tWZ)->contextMap->virtMap[MAP_WIDTH-1][oldy]->getTypeID() != 3)
            moveEntTo(tgt, tWX-1, tWY, tWZ, MAP_WIDTH-1, oldy);
        return;
    }
    else if(!moved && oldx+x >= MAP_WIDTH)
    {
        if(tWX == wX-1)
            tWX = -1;
        
        if(!eMap->at(tWX+1).at(tWY).at(tWZ)->contextMap->virtMap[1][oldy]->blocked && eMap->at(tWX+1).at(tWY).at(tWZ)->contextMap->virtMap[1][oldy]->getTypeID() != 3)
            moveEntTo(tgt, tWX+1, tWY, tWZ, 1, oldy);
        return;
    }
    else if(!moved && oldy+y <= 0)
    {
        if(tWY == 0)
            tWY = wY;
        
        if(!eMap->at(tWX).at(tWY-1).at(tWZ)->contextMap->virtMap[oldx][MAP_HEIGHT-1]->blocked && eMap->at(tWX).at(tWY-1).at(tWZ)->contextMap->virtMap[oldx][MAP_HEIGHT-1]->getTypeID() != 3)
            moveEntTo(tgt, tWX, tWY-1, tWZ, oldx, MAP_HEIGHT-1);
        return;
    }
    else if(!moved && oldy+y >= MAP_HEIGHT)
    {
        if(tWY == wY-1)
            tWY = -1;
        
        if(!eMap->at(tWX).at(tWY+1).at(tWZ)->contextMap->virtMap[oldx][1]->blocked  && eMap->at(tWX).at(tWY+1).at(tWZ)->contextMap->virtMap[oldx][1]->getTypeID() != 3)
            moveEntTo(tgt, tWX, tWY+1, tWZ, oldx, 1);
        return;
    }
}



void WorldMap::changEntZ(Entity *tgt, int z)
{
    
    int origZ;
    
    origZ = tgt->wZ;
    
    if(origZ+z < 0)
    {
        
            return;
        
    }
    else if(origZ+z == wZ)
    {
        
            return;
        
    }
    else if( z == 1)
    {
        if(!eMap->at(tgt->wX).at(tgt->wY).at(origZ+z)->contextMap->virtMap[tgt->posX()][tgt->posY()]->blocked && eMap->at(tgt->wX).at(tgt->wY).at(tgt->wZ)->contextMap->virtMap[tgt->posX()][tgt->posY()]->getTypeID() == 4 && eMap->at(tgt->wX).at(tgt->wY).at(origZ+z)->contextMap->virtMap[tgt->posX()][tgt->posY()]->getTypeID() == 3)
        {
            for(int x=0; x < MAP_WIDTH; x++)
            {
                for(int y=0; y < MAP_HEIGHT; y++)
                {
                    tgt->returnCMap()->cMap[x][y]->explored = false;
                }
            }
            
            moveEntTo(tgt, tgt->wX, tgt->wY, origZ+z, tgt->posX(), tgt->posY());
            
        }
        
        
        
    }
    else if( z == -1)
    {
        if(!eMap->at(tgt->wX).at(tgt->wY).at(origZ+z)->contextMap->virtMap[tgt->posX()][tgt->posY()]->blocked && eMap->at(tgt->wX).at(tgt->wY).at(tgt->wZ-1)->contextMap->virtMap[tgt->posX()][tgt->posY()]->getTypeID() == 4 && eMap->at(tgt->wX).at(tgt->wY).at(tgt->wZ)->contextMap->virtMap[tgt->posX()][tgt->posY()]->getTypeID() == 3)
        {
            for(int x=0; x < MAP_WIDTH; x++)
            {
                for(int y=0; y < MAP_HEIGHT; y++)
                {
                    tgt->returnCMap()->cMap[x][y]->explored = false;
                }
            }
            
            moveEntTo(tgt, tgt->wX, tgt->wY, origZ+z, tgt->posX(), tgt->posY());
        
            
        }
    }
    
    
    
}


void WorldMap::moveEntTo(Entity *tgt, int x, int y, int z, int px, int py)
{
    
    
    
    eMap->at(tgt->wX).at(tgt->wY).at(tgt->wZ)->removeFromEntMap(tgt);
    
    tgt->setWorldPosition(x, y, z);
    tgt->cMap->deleteMap();
    tgt->cMap->clearMap();
    
    eMap->at(x).at(y).at(z)->addToMapAt(tgt, px, py);
    
    
    
}



EntityMap *WorldMap::getNextEntMap(Entity *tgt, int dir)
{
    int tWX, tWY;
    
    tWX = tgt->wX;
    tWY = tgt->wY;
    //tWZ = tgt->wZ;
    
    if (dir == 1)
    {
        if(tWX != 0 && tgt->wY+1 == wY)
        {
            return eMap->at(tgt->wX-1).at(0).at(tgt->wZ);
        }
        else if(tWX != 0 && tgt->wY+1 != wY)
        {
            return eMap->at(tgt->wX-1).at(tgt->wY+1).at(tgt->wZ);
        }
        else if(tWX == 0 && tgt->wY+1 == wY)
        {
            return eMap->at(wX-1).at(0).at(tgt->wZ);
        }
        else if(tgt->wX == 0 && tgt->wY+1 != wY)
        {
            return eMap->at(wX-1).at(tgt->wY+1).at(tgt->wZ);
        }
        
    }
    else if(dir == 2)
    {
        if(tWY == wY-1)
        {
            return eMap->at(tgt->wX).at(0).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX).at(tgt->wY+1).at(tgt->wZ);
        }
        
    }
    else if(dir == 3)
    {
        if(tgt->wX+1 != wX && tgt->wY+1 != wY)
        {
            return eMap->at(tgt->wX+1).at(tgt->wY+1).at(tgt->wZ);
        }
        else if(tgt->wX+1 != wX && tgt->wY+1 == wY)
        {
            return eMap->at(tgt->wX+1).at(0).at(tgt->wZ);
        }
        else if(tgt->wX+1 == wX && tgt->wY+1 != wY)
        {
            return eMap->at(0).at(tgt->wY+1).at(tgt->wZ);
        }
        else if(tgt->wX+1 == wX && tgt->wY+1 == wY)
        {
            return eMap->at(0).at(0).at(tgt->wZ);
        }
    }
    else if(dir == 4)
    {
        if(tWX == 0)
        {
            return eMap->at(wX-1).at(tgt->wY).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX-1).at(tgt->wY).at(tgt->wZ);
        }
        
    }
    else if(dir == 6)
    {
        if(tWX == wX-1)
        {
            return eMap->at(0).at(tgt->wY).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX+1).at(tgt->wY).at(tgt->wZ);
        }
    }
    else if(dir == 7)
    {
        if(tWX != 0 && tgt->wY != 0)
        {
            return eMap->at(tgt->wX-1).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX != 0 && tgt->wY == 0)
        {
            return eMap->at(tgt->wX-1).at(wY-1).at(tgt->wZ);
        }
        else if(tWX == 0 && tgt->wY != wY)
        {
            return eMap->at(wX-1).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX == 0 && tgt->wY == wY)
        {
            return eMap->at(wX-1).at(wY-1).at(tgt->wZ);
        }
    }
    else if(dir == 8)
    {
        if(tWY == 0)
        {
            return eMap->at(tgt->wX).at(wY-1).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX).at(tgt->wY-1).at(tgt->wZ);
        }
    }
    else if(dir == 9)
    {
        if(tWX+1 != wX && tgt->wY != 0)
        {
            return eMap->at(tgt->wX+1).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX+1 != wX && tgt->wY == 0)
        {
            return eMap->at(tgt->wX+1).at(wY-1).at(tgt->wZ);
        }
        else if(tWX+1 == wX && tgt->wY != wY)
        {
            return eMap->at(0).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX+1 == wX && tgt->wY == wY)
        {
            return eMap->at(0).at(wY-1).at(tgt->wZ);
        }
    }
    
    else
        return nullptr;
    
    
}



EntityMap *WorldMap::getNextEntMap(EntityMap *tgt, int dir)
{
    
    int tWX, tWY;
    
    tWX = tgt->wX;
    tWY = tgt->wY;
    //tWZ = tgt->wZ;
    
    if (dir == 1)
    {
        if(tWX != 0 && tgt->wY+1 == wY)
        {
            return eMap->at(tgt->wX-1).at(0).at(tgt->wZ);
        }
        else if(tWX != 0 && tgt->wY+1 != wY)
        {
            return eMap->at(tgt->wX-1).at(tgt->wY+1).at(tgt->wZ);
        }
        else if(tWX == 0 && tgt->wY+1 == wY)
        {
            return eMap->at(wX-1).at(0).at(tgt->wZ);
        }
        else if(tgt->wX == 0 && tgt->wY+1 != wY)
        {
            return eMap->at(wX-1).at(tgt->wY+1).at(tgt->wZ);
        }
        
    }
    else if(dir == 2)
    {
        if(tWY == wY-1)
        {
            return eMap->at(tgt->wX).at(0).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX).at(tgt->wY+1).at(tgt->wZ);
        }
        
    }
    else if(dir == 3)
    {
        if(tgt->wX+1 != wX && tgt->wY+1 != wY)
        {
            return eMap->at(tgt->wX+1).at(tgt->wY+1).at(tgt->wZ);
        }
        else if(tgt->wX+1 != wX && tgt->wY+1 == wY)
        {
            return eMap->at(tgt->wX+1).at(0).at(tgt->wZ);
        }
        else if(tgt->wX+1 == wX && tgt->wY+1 != wY)
        {
            return eMap->at(0).at(tgt->wY+1).at(tgt->wZ);
        }
        else if(tgt->wX+1 == wX && tgt->wY+1 == wY)
        {
            return eMap->at(0).at(0).at(tgt->wZ);
        }
    }
    else if(dir == 4)
    {
        if(tWX == 0)
        {
            return eMap->at(wX-1).at(tgt->wY).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX-1).at(tgt->wY).at(tgt->wZ);
        }
        
    }
    else if(dir == 6)
    {
        if(tWX == wX-1)
        {
            return eMap->at(0).at(tgt->wY).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX+1).at(tgt->wY).at(tgt->wZ);
        }
    }
    else if(dir == 7)
    {
        if(tWX != 0 && tgt->wY != 0)
        {
            return eMap->at(tgt->wX-1).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX != 0 && tgt->wY == 0)
        {
            return eMap->at(tgt->wX-1).at(wY-1).at(tgt->wZ);
        }
        else if(tWX == 0 && tgt->wY != wY)
        {
            return eMap->at(wX-1).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX == 0 && tgt->wY == wY)
        {
            return eMap->at(wX-1).at(wY-1).at(tgt->wZ);
        }
    }
    else if(dir == 8)
    {
        if(tWY == 0)
        {
            return eMap->at(tgt->wX).at(wY-1).at(tgt->wZ);
        }
        else
        {
            return eMap->at(tgt->wX).at(tgt->wY-1).at(tgt->wZ);
        }
    }
    else if(dir == 9)
    {
        if(tWX+1 != wX && tgt->wY != 0)
        {
            return eMap->at(tgt->wX+1).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX+1 != wX && tgt->wY == 0)
        {
            return eMap->at(tgt->wX+1).at(wY-1).at(tgt->wZ);
        }
        else if(tWX+1 == wX && tgt->wY != wY)
        {
            return eMap->at(0).at(tgt->wY-1).at(tgt->wZ);
        }
        else if(tWX+1 == wX && tgt->wY == wY)
        {
            return eMap->at(0).at(wY-1).at(tgt->wZ);
        }
    }
    
    else
        return nullptr;
    
    
    
    
    
}




EntityMap *WorldMap::getEntityZ(EntityMap *tgt, int z)
{
    
    int origZ;
    
    origZ = tgt->wZ;
    
    if(origZ+z < 0)
    {
        
        return nullptr;
        
    }
    else if(origZ+z >= wZ)
    {
        
        return nullptr;
        
    }
    else
    {
        return eMap->at(tgt->wX).at(tgt->wY).at(origZ+z);
                    
    }
    
    
    
}







