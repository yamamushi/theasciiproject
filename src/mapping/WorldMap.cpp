//
//  WorldMap.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 2/28/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "WorldMap.h"
#include <memory>
#include <vector>
#include "../mapping/TileMap.h"
#include "../mapping/EntityMap.h"
#include "../serialization/Boost_Serialization.h"


void WorldMap::init(){
    
    initGlobalTileMap();
    //initGlobalEntityMap();
    
}



void WorldMap::initGlobalTileMap(){
    
    for(int x=0; x<X; x++){
        std::vector< std::vector<TileMap *> > layer;
        for(int y=0; y<Y; y++){
            std::vector<TileMap *> row;
            for(int z=0; z<Z; z++){
                TileMap *tileMap = new TileMap(mapX, mapY);
                row.push_back(tileMap);
            }
            layer.push_back(row);
        }
        globalTileMap.push_back(layer);
    }
    
}


void WorldMap::initGlobalEntityMap(){
    
    
    
}