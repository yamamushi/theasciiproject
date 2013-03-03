#pragma once
/*
 
 TileMap.h
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 Our TileMap class, used for storing Tiles...
 
 */

#include <memory>
#include <vector>
#include <string>

#include "../serialization/Boost_Serialization.h"
#include "Tile.h"

class TileMap {
    
private:
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & length;
        ar & width;
        ar & virtualMap;
    }
    
    int length, width;

    
    void init();
    void fillSolid();
    
public:
    
    TileMap(){};
    TileMap(int l, int w) : length(l), width(w){init();};
    
    std::vector< std::vector<Tile *> > virtualMap;
    
    void backupToDisk(std::string path);
    
    ~TileMap(){};
    
    int getLength(){return length;}
    int getWidth(){return width;}
    
};
