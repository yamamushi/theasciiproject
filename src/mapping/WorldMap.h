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



class WorldMap {
    
private:
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & X;
        ar & Y;
        ar & Z;
        ar & globalTileMap;
        ar & globalEntityMap;
    }
    
    // Global Map Dimensions
    int X,Y,Z;
    
    // Storage Container for TileMaps
    std::vector< std::vector< std::vector< std::unique_ptr<TileMap> > > > globalTileMap;
    
    // Storage Container for EntityMaps
    std::vector< std::vector< std::vector< std::unique_ptr<EntityMap> > > > globalEntityMap;
    
    
public:
    
    WorldMap( int x, int y, int z) : X(x), Y(y), Z(z){};
    
    ~WorldMap(){};
    
};
