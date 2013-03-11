#pragma once
//
//  WorldMap.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 2/28/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "../serialization/Boost_Serialization.h"
#include "TileMap.h"
#include "Tile.h"
#include "EntityMap.h"
#include <vector>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <string>



class WorldMap : public std::enable_shared_from_this<WorldMap>{
    
private:
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & X;
        ar & Y;
        ar & Z;
        ar & mapX;
        ar & mapY;
        ar & globalTileMap;
        //ar & globalEntityMap;
    }
    
    // Global Map Dimensions
    int X,Y,Z;
    int worldTileLength, worldTileWidth, worldTileHeight;
    
    // TileMap Dimensions
    int mapX, mapY;
    
    // Config Setting for Exports/Imports
    std::string rootFS;
    
    // Storage Container for TileMaps
    std::vector< std::vector< std::vector< boost::shared_ptr<TileMap> > > > globalTileMap;
    
    // Storage Container for EntityMaps
    //std::vector< std::vector< std::vector< boost::shared_ptr<EntityMap> > > > globalEntityMap;
    
    void init();
    void initGlobalTileMap();
    void initGlobalEntityMap();
    
    void exportTileMap(int x, int y, int z, boost::shared_ptr<TileMap> exportMap);
    boost::shared_ptr<TileMap> importTileMap(int x, int y, int z);
    
    
public:
    
    WorldMap(){};
    WorldMap( int x, int y, int z, int tX, int tY, std::string rootFS) : X(x), Y(y), Z(z), mapX(tX), mapY(tY), rootFS(rootFS){init();};
    
    ~WorldMap(){};
    
    int getX(){return X;};
    int getY(){return Y;};
    int getZ(){return Z;};
    
    int returnWorldLength(){return worldTileLength;};
    int returnWorldWidth(){return worldTileWidth;};
    int returnWorldHeight(){return worldTileHeight;};
    
    TileMap* getTileMap(int posx, int posy, int posz);
    Tile* getTileAt(int posx, int posy, int posz); // NOTE - This is in the global context, not the TileMap context!
    Tile* AltGetTileAt(int posx, int posy, int posz);

};
