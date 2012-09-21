/*
 * =====================================================================================
 *
 *       Filename:  WorldMap.h
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


#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class EntityMap;
class Entity;

class WorldMap {
    
private:
    
    
public:
    
    
    int wX, wY, wZ;
    int cX, cY, cZ;
       
    //boost::multi_array<3, EntityMap *> eMap;
    //std::vector<std::vector<std::vector<TileMap*> > > *tMap;
    std::vector<std::vector<std::vector<EntityMap*> > > *eMap;
    

    WorldMap(int x=10, int y=10, int z=10) : wX(x), wY(y), wZ(z), cX(x/2), cY(y/2), cZ(z/2)
    {
        
        cout << "World Latitude = " << wX << endl;
        cout << "World Longitude = " << wY << endl;
        cout << "World Height = " << wZ << endl;
        
        //tMap = new std::vector<std::vector<std::vector<TileMap*> > >(wX, std::vector<std::vector<TileMap*> >(wY, std::vector<TileMap*>(wZ, new TileMap(MAP_WIDTH, MAP_HEIGHT))));
        eMap = new std::vector<std::vector<std::vector<EntityMap*> > >(wX, std::vector<std::vector<EntityMap*> >(wY, std::vector<EntityMap*>(wZ, nullptr) ) );

        
    };
    
    void initWorldMap();

    
    
    void addEntToCenter(Entity *tgt);
    void removeEnt(Entity *tgt);
    
    void moveEnt(Entity *tgt, int x, int y);
    void moveEntTo(Entity *tgt, int x, int y, int z, int px, int py);
    
    void changEntZ(Entity *tgt, int z);
    
    
    
    EntityMap *getNextEntMap(Entity *tgt, int dir);
    EntityMap *getNextEntMap(EntityMap *tgt, int dir);
    EntityMap *getEntityZ(EntityMap *tgt, int z);
    
};
