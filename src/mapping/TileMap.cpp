/*
 
 TileMap.cpp
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 TileMap Class functions
 
 */


#include <memory>
#include <vector>
#include <iostream>

#include "../serialization/Boost_Serialization.h"
#include "TileMap.h"
#include "Tile.h"


void TileMap::init(){
    
    std::cout << length << std::endl;
    std::cout << width << std::endl;
    
    for(int x=0; x<length; x++){        
        std::vector<Tile *> row;
        for(int y=0; y<width; y++){            
            Tile *newTile = new Tile(x, y, u8"\u2550");
            row.push_back(newTile);
        }
        virtualMap.push_back(row);
    }
}


void TileMap::fillSolid(){
    
    for(int x=0; x<length; x++){
        for( int y=0; y<width; y++){
            
        }
    }
    
};
