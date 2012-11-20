#pragma once
/*
 * =====================================================================================
 *
 *       Filename:  TileMap.h
 *
 *    Description:  This object stores the position of Tiles on the Map.
 *
 *        Version:  1.0
 *        Created:  07/05/2012
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


#include "BoostLibs.h"
#include "constants.h"
#include "Tiles.h"


class TileMap {
private:
    friend class boost::serialization::access;
    //Tile * vMap[MAP_WIDTH][MAP_HEIGHT];
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & wid;
        ar & hig;
        ar & posX;
        ar & posY;
        ar & posZ;
        ar & rooms;
        ar & numRooms;
        ar & halls;
        ar & numHalls;
        
        int p, q;
        for(p = 0; p < MAP_WIDTH; p++){
            for(q = 0; q < MAP_HEIGHT; q++){
                ar & virtMap[p][q];
            }
            
        }
        
    }
    
    int x, y, z, i;
    
    
public:
    int wid, hig;
    int posX, posY, posZ;
    
    Room *rooms[MAX_ROOMS];
    int numRooms;
    Hall *halls[MAX_HALLS];
    int numHalls;
    
    Tile * virtMap[MAP_WIDTH][MAP_HEIGHT];

    
    TileMap(){};
    TileMap(int i, int z);
    void initMap(int i, int z);
    
    virtual ~TileMap(){};
    
    void indexMap(int x, int y, int z);
    
    void clearMap();
    void refreshMap();
    void fillMap();
    
    bool checkBounds(int, int);
    
    void createRoom(int, int, int, int);
    void drawRoom(int i);
    void drawAllRooms();
    
    void createHall(int, int, int, int);
    void drawHall(int i);
    void drawAllHalls();
    
    
    void orientWall(int x, int y);
    void orientWalls();
    void orientWalls(int x1, int y1, int x2, int y2);
    
    void importRoom(Room *source);
    void importAllRooms(TileMap *source);
    void clearRooms();
    void clearRoom(int x);
    
    void importHall(Hall *source);
    void importAllHalls(TileMap *source);
    void clearHalls();
    void clearHall(int x);
    
    void copyVirtMap(TileMap *source);
    void importMap(TileMap *source);
    
    
    void removeTile(int x, int y);
    void floorTile(int x, int y);
    void placeTile(int x, int y);
    
    void wallTile(int x, int y);
    void slopeTile(int x, int y);
    
    
    void digHole(int x, int y);
    void airTile(int x, int y);
    
    void replaceTile(int x, int y, Tile *src);
    
    
    void airMap();
};

