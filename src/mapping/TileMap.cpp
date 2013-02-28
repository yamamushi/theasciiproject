/*
 
 TileMap.cpp
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 TileMap Class functions
 
 */


#include <memory>
#include <vector>

#include "../serialization/Boost_Serialization.h"
#include "TileMap.h"
#include "Tile.h"


void TileMap::init(){
    
    for(int x=0; x<length; x++){
        for(int y=0; y<width; y++){
            
            std::shared_ptr<Tile> newTile(new Tile(x, y));
            virtualMap[x].push_back(newTile);
            
        }
    }
    
}


void TileMap::fillSolid(){
    
    for(int x=0; x<length; x++){
        for( int y=0; y<width; y++){
            
        }
    } 
    
};
