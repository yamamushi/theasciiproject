/*
 * =====================================================================================
 *
 *       Filename:  EntityMap.cpp
 *
 *    Description:  EntityMap is an object which stores the location of all
 *                  Entities on the "Map".
 *
 *        Version:  1.0
 *        Created:  07/11/2012
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


#include <iostream>

#include "libtcod/libtcod.hpp"

#include "EntityMap.h"
#include "TileMap.h"
#include "FovLib.h"
#include "RenderMap.h"
#include "Entities.h"
#include "WorldMap.h"

using std::cout;
using std::endl;



/*
 *
 * 		Here begins our EntityMap object.
 *
 * 	The purpose of this object is to store a
 * 	static-sized 2-dimensional array of vectors.
 *
 * 	Each vector is a list of Entities, thus
 * 	A seemingly "infinite" amount of entities can
 * 	exist in one space of a map at one time.
 *
 * 	This Object will thus return the color map
 * 	(which essentially allows the graphics rendering
 * 	engine to render entities without doing
 * 	much thought on it's own).
 *
 *	This Object will also allow each individual entity
 *	to gather information about other entities in
 *	its own context.
 *
 *
 */


EntityMap::EntityMap(int x, int y, TileMap *map){
    
	initEntityMap(x, y, map);
    
}

void EntityMap::initEntityMap(int x, int y, TileMap *map){
    
	width = x;
	height = y;
    
    contextMap = map;
    
    fovLib = new FovLib(map);
    
    
    rMap = new RenderMap(contextMap);
    rMap->initEntMap(this);
    
    deleting = false;
    
    
}



void EntityMap::initWorldMap(WorldMap *WMap, int x, int y, int z)
{
    
    wMap = WMap;
    wX = x;
    wY = y;
    wZ = z;
    
    
    refreshLightMap();
    refreshRenderMap();
}





void EntityMap::addToMap(Entity *entity){
    
    refreshLightMap();
    refreshRenderMap();
    
    
	Entity *src = entity;
	int x, y;
    
	x = src->posX();
	y = src->posY();
	pos[x][y].push_back(src);
    src->init_in_world(fovLib);
    src->setEntityMap(this);
    
    src->associateClient(rMap);
    src->move(width/2, height/2);
    
    
}



void EntityMap::addToMapAt(Entity *entity, int x, int y){
    
    refreshLightMap();
    refreshRenderMap();
    
    
	Entity *src = entity;
    src->setPos(x, y);
	
	pos[x][y].push_back(src);
    src->init_in_world(fovLib);
    src->setEntityMap(this);
    
    src->associateClient(rMap);
    src->move(0,0);
    
    
}






void EntityMap::placeInRandomRoom(Entity *ent)
{
    TCODRandom *rng = new TCODRandom();
    int room = rng->getInt( 1, MAX_ROOMS-1);  //derp.
    
    ent->move(contextMap->rooms[room]->cX, contextMap->rooms[room]->cY);
    delete rng;
    
}




void EntityMap::removeFromEntMap(Entity *ent)
{
    
    deleting = true;
    
	int x, y, z;
    
    std::string srcName = ent->getEntName();
    
	for ( x = 0; x < width; x++){
		for ( y = 0; y < height; y++){
			if (!(pos[x][y].empty())){
				for ( z = 0; z < pos[x][y].size(); z++){
                    if(pos[x][y].at(z)->getEntName() == srcName)
                    {
                        pos[x][y].erase(pos[x][y].begin()+z);
                        
                        //cout << "erased at " << x << " " <<  y << " " <<  z << endl;
                        break;
                    }
                }
			}
		}
	}
    
    deleting = false;
    
    refreshLightMap();
    refreshRenderMap();
    
}


void EntityMap::initAllEnts(){
    
    
	int x, y, z;
    
    if (!deleting)
    {
        for ( x = 0; x < width; x++){
            for ( y = 0; y < height; y++){
                if (!(pos[x][y].empty())){
                    for ( z = 0; z < pos[x][y].size(); z++){
                        pos[x][y].at(z)->init_in_world(fovLib);
                        pos[x][y].at(z)->setEntityMap(this);
                        
                        if(deleting)
                            break;
                    }
                }
            }
        }
    }
    
    refreshLightMap();
    refreshRenderMap();
}

void EntityMap::refreshEntityMap(){
    
    refreshRenderMap();
    
    int x, y, z;
    
    if (!deleting)
    {
        
        
        for ( x = 0; x < width; x++){
            for ( y = 0; y < height; y++){
                if( !(pos[x][y].empty()) ){
                    for ( z = 0; z < pos[x][y].size(); z++){
                        // check each entity in this vector
                        // move entity to new vector
                        // coordinates at x and y
                        
                        // First we check to see if this entities
                        // coordinates differ from our own:
                        Entity *cur = pos[x][y].back();
                        
                        if ( (x != (cur->posX())) || (y != (cur->posY())) ){
                            // now we do some magic
                            int newX = cur->posX();
                            int newY = cur->posY();
                            
                            pos[newX][newY].push_back(cur);
                            pos[x][y].pop_back();
                            
                            if(deleting)
                                break;
                            
                        }
                    }
                }
            }
        }
    }
    
    
    
}


void EntityMap::refreshRenderMap()
{
    refreshTileMap();
    
    //if(wZ > wMap->cZ)
    //{
    for(int x = 0; x < MAP_WIDTH; x++)
    {
        for(int y = 0; y < MAP_HEIGHT; y++)
        {
            if(wMap->getEntityZ(this, -1) != nullptr)
            {
                
                if(wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->getTypeID() == 1 && contextMap->virtMap[x][y]->getTypeID() == 3)
                {
                    
                    contextMap->floorTile(x, y);;
                    
                }
                else if(wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->getTypeID() != 3 && contextMap->virtMap[x][y]->getTypeID() == 3)
                {
                    contextMap->virtMap[x][y]->setHSV(wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->HD, wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->HD, wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->HD);
                    contextMap->virtMap[x][y]->setHSV(wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->HD, wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->SD, wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->VD, true);
                    
                    if(wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->getTypeID() == 4)
                        contextMap->virtMap[x][y]->setSymbol((wchar_t*)L"\u25BC");
                    else
                        contextMap->virtMap[x][y]->setSymbol(wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->getSymbol());
                    
                }
                else if(wMap->getEntityZ(this, -1)->contextMap->virtMap[x][y]->getTypeID() == 3 && contextMap->virtMap[x][y]->getTypeID() == 3)
                {
                    
                    contextMap->airTile(x, y);
                    
                }
                
            }
            
        }
    }
    
    //}
    
    rMap->refreshMap();
}

void EntityMap::refreshLightMap()
{
    
    for(int x=0; x < MAP_WIDTH; x++)
    {
        for(int y=0; y < MAP_HEIGHT; y++)
        {
            contextMap->virtMap[x][y]->isLit = false;   
        }
    }
    
    if(wMap->getEntityZ(this, 1) != nullptr)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            for(int y = 0; y < MAP_HEIGHT; y++)
            {
                //contextMap->virtMap[x][y]->isLit = false;
                if(wMap->getEntityZ(this, 1)->contextMap->virtMap[x][y]->getTypeID() == 3 )//&& contextMap->virtMap[x][y]->getTypeID() != 3)
                {
                    
                    bool uncovered = true;
                    bool finished = false;
                    int countZ = 1;
                    
                    while(!finished)
                    {
                        if(wMap->getEntityZ(this, countZ) != nullptr)
                        {
                            if(wMap->getEntityZ(this, countZ)->contextMap->virtMap[x][y]->getTypeID() == 3)
                            {
                                uncovered = true;
                            }
                            else
                            {
                                uncovered = false;
                                finished = true;
                            }
                            
                        }
                        else
                        {
                            uncovered = true;
                            finished = true;
                            
                        }
                        countZ++;
                    }
                    
                    if(uncovered)
                    {
                        
                        int lightSpread;
                        
                        lightSpread =  (wZ-(wMap->cZ-2));   //(int)floor(log(wZ/(wMap->wZ))/(log(2)));
                        
                        if(lightSpread > 0)
                        {
                            fovLib->refreshFov(this, x, y, lightSpread);
                            
                        }
                    }
                    
                }
                
            }
            
        }
        
    }
    rMap->refreshMap();
    
}




void EntityMap::refreshTileMap()
{
    contextMap->orientWalls();
}


bool EntityMap::checkOccupied(int x, int y)
{
    
    
	if ( !(pos[x][y].empty()) )
    {
		return true;
	}
	else
		return false;
}

Entity * EntityMap::outputLastEntity(int x, int y)
{
    
	if( !(pos[x][y].empty())  && !deleting )
    {
        Entity *current = pos[x][y].back();
        return current;
	}
    else
        return nullptr;
}

void EntityMap::refreshFovFor(Entity *tgt)
{
    
    fovLib->refreshFov(tgt, 7);
    
}

