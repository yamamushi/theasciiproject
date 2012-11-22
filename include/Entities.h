#pragma once
/*
 * =====================================================================================
 *
 *       Filename:  Entities.h
 *
 *    Description:  This object defines the behavior of our "Entities", ie
 *                  The necessary functions for an entity to exist on the "Map"
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:42:54 AM
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
#include "EntityMap.h"

class Tile;
class ClientMap;
class FovLib;
class RenderMap;
class WorldMap;


class Entity {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & entName;
        ar & wSymbol;
        ar & X;
        ar & Y;
        ar & wX;
        ar & wY;
        ar & wZ;
        ar & H;
        ar & S;
        ar & V;
    }
    
    
    int X, Y;
    
    std::string entName;
    
    
    wchar_t *symbol;
    
    
    
    unsigned int TypeID, SubTypeID;
    unsigned int UID;
    
    bool initialized, clientActive;
    
    
    
    FovLib *FOV;
    
    RenderMap *rMap;
    WorldMap *wMap;
    
public:
    
    TileMap *world;
    EntityMap *entMap;
    ClientMap *cMap;
    
    int wX, wY, wZ;
    float H, S, V;
    int R, G, B;
    std::wstring wSymbol;
    
    
    Entity()
    {
        world = nullptr;
        cMap = nullptr;
        int x, y;
        for (x = 0; x < MAP_WIDTH; x++) {
            for (y = 0; y < MAP_HEIGHT; y++) {
                fov[x][y] = false;
            }
        }
    };
    
    Entity(std::string entName_, std::wstring wsymbol_, int x, int y, int wx, int wy, int wz, int h, int s, int v) : entName(entName_), wSymbol(wsymbol_), X(x), Y(y), wX(wx), wY(wy), wZ(wz), H(h), S(s), V(v) { world = nullptr; cMap = nullptr; symbol = (wchar_t *)wSymbol.c_str();};
    Entity(wchar_t *sym){ cMap = nullptr; init_entity(sym);};
    
    
    
    
    void setPos(int x, int y);
    void init_entity( wchar_t *symbol );
    
    void refreshFov(int radius);
    int posX();
    int posY();
    bool fov[MAP_WIDTH][MAP_HEIGHT];
    bool sharedFov[MAP_WIDTH][MAP_HEIGHT];
    
    
    void init_in_world(FovLib *FOV);
    void setGlobal(WorldMap *WMap);
    
    void setEntName(std::string entName_);
    std::string getEntName();
    
    
    wchar_t *getSymbol();
    void setSymbol(wchar_t *ch);
    
    void setTypeID(int i);
    void setSubTypeID(int i);
    
    
    
    bool isInitialized();
    void associateClient(RenderMap *RMap);
    
    bool getAssociated();
    ClientMap * returnCMap();
    void clientFovSync(bool forceReset=false);
    
    
    void setWorldPosition(int x, int y, int z);
    
    
    
    void setEntityMap(EntityMap *map);
    
    
    bool move(int dx, int dy);
    void move_self(int dx, int dy);
    
    bool removeWall(int dx, int dy);
    bool placeWall(int dx, int dy);
    
    bool placeFloor(int dx, int dy);
    bool digHole(int dx, int dy);
    bool digUp();
    bool digDown();
    
};




// These entities are for testing purposes only
// and will be moved in the coming days.


class Monster : public Entity {
    
public:
    
    Monster();
    
};


class Player : public Entity {
    
public:
    Player();
    
};


class Goblin : public Entity {
    
public:
    Goblin();
    
};
