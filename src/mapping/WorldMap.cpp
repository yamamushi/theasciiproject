//
//  WorldMap.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 2/28/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "../serialization/Boost_Serialization.h"
#include "WorldMap.h"
#include <memory>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "../mapping/TileMap.h"
#include "../mapping/EntityMap.h"



void WorldMap::init(){
    
    initGlobalTileMap();
    //initGlobalEntityMap();
    
}



void WorldMap::initGlobalTileMap(){
    
    for(int x=0; x<X; x++){
        std::vector< std::vector< boost::shared_ptr<TileMap> > > layer;
        for(int y=0; y<Y; y++){
            std::vector< boost::shared_ptr<TileMap> > row;
            for(int z=0; z<Z; z++){
                boost::shared_ptr<TileMap> tileMap(new TileMap(mapX, mapY));
                row.push_back(tileMap);
            }
            layer.push_back(row);
        }
        globalTileMap.push_back(layer);
    }
    
}


void WorldMap::initGlobalEntityMap(){
    
    
    
}