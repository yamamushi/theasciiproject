#pragma once
/*
 
 TileMap.h
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 Our TileMap class, used for storing Tiles...
 
 */

#include "../serialization/Boost_Serialization.h"
#include <memory>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "Tile.h"

class TileMap : public std::enable_shared_from_this<TileMap>{
    
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
    
    std::vector< std::vector<boost::shared_ptr<Tile> > > virtualMap;
    
    void backupToDisk(std::string path);
    
    ~TileMap(){};
    
    int getLength(){return length;}
    int getWidth(){return width;}
    
    Tile* getTilePtr(int x, int y){return virtualMap.at(x).at(y).get();}
    
};

BOOST_SERIALIZATION_SHARED_PTR(TileMap)
//BOOST_CLASS_EXPORT(TileMap)
