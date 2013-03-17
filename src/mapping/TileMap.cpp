/*
 
 TileMap.cpp
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 TileMap Class functions
 
 */


#include <memory>
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "../serialization/Boost_Serialization.h"
#include "TileMap.h"
#include "Tile.h"


void TileMap::init(){
    
    for(int x=0; x<length; x++){        
        std::vector<boost::shared_ptr<Tile> > row;
        for(int y=0; y<width; y++){            
            //boost::shared_ptr<Tile> newTile(new Tile(x, y, u8"\u2327"));
            boost::shared_ptr<Tile> newTile(new Tile(0x2327));
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
