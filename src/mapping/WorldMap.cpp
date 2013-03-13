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
#include <string>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/EntityMap.h"
#include "../utils/Random.h"


void WorldMap::init(){
    
    worldTileLength = X * mapX;
    worldTileWidth = Y * mapY;
    worldTileHeight = Z;
    
    Random rand;
    WorldID = rand.rand_crypt();
    
    initGlobalTileMap();
    //initGlobalEntityMap();
    
}



void WorldMap::initGlobalTileMap(){
    
   // TileMapMutexTable.resize(X*Y*Z);
   // TileMapLoadedTable.resize(X*Y*Z);
    
    for(int x=0; x<X; x++){
        
        std::vector< std::vector< boost::shared_ptr<TileMap> > > globalTileMap_layer;
        std::vector< std::vector< bool> > tileMapLoadedTable_layer;
        
        for(int y=0; y<Y; y++){
        
            std::vector< boost::shared_ptr<TileMap> > globalTileMap_row;
            std::vector< bool> tileMapLoadedTable_row;
            
            for(int z=0; z<Z; z++){
                
                boost::shared_ptr<TileMap> tileMap(new TileMap(mapX, mapY, x, y, z));
                tileMap->setOwnerWorldID(WorldID);
                globalTileMap_row.push_back(tileMap);
                exportTileMap(x, y, z, tileMap);
                
                tileMapLoadedTable_row.push_back(false);

            }
            
            globalTileMap_layer.push_back(globalTileMap_row);
            tileMapLoadedTable_layer.push_back(tileMapLoadedTable_row);
            
        }
        
        globalTileMap.push_back(globalTileMap_layer);
        TileMapLoadedTable.push_back(tileMapLoadedTable_layer);
        
    }
    
}


void WorldMap::initGlobalEntityMap(){
    
    
    
}

void WorldMap::exportTileMap(int x, int y, int z, boost::shared_ptr<TileMap> exportMap){
    
    std::string fileName(rootFS + "/maps/tilemaps/" + boost::lexical_cast<std::string>(x) + "_" +
                         boost::lexical_cast<std::string>(y) + "_" + boost::lexical_cast<std::string>(z) + ".tlm");
    std::ofstream outputMap(fileName);
    boost::archive::text_oarchive world_oarchive(outputMap);
    
    TileMap *tileMapOut = exportMap.get();
    world_oarchive << tileMapOut;
    outputMap.close();
    
}

boost::shared_ptr<TileMap> WorldMap::importTileMap(int x, int y, int z){
    
    TileMap *importMap;
    std::string fileName( rootFS + "/maps/tilemaps/" + boost::lexical_cast<std::string>(x) + "_" +
                         boost::lexical_cast<std::string>(y) + "_" + boost::lexical_cast<std::string>(z) + ".tlm");
    
    std::ifstream inputMap(fileName);
    boost::archive::text_iarchive inputTextArchive(inputMap);
    
    inputTextArchive & importMap;
    inputMap.close();
    
    boost::shared_ptr<TileMap> returnMap(importMap);
    
    return returnMap;
    
}


TileMap* WorldMap::getTileMap(int posx, int posy, int posz){
    
    if(posx >= X || posy >= Y || posz >= Z)
        return nullptr;
    
    //importTileMap(posx, posy, posz);
    
    return globalTileMap.at(posx).at(posy).at(posz).get();
}


Tile* WorldMap::getTileAt(int posx, int posy, int posz){
    
    if( posx >= worldTileLength || posy >= worldTileLength || posz >= worldTileHeight )
        return nullptr;
    
    int realTileMapX = (posx / mapX);
    int realTileMapY = (posy / mapY);
    
    int realTileX = (posx % mapX);
    int realTileY = (posy % mapY);
    
    TileMap *realTileMap = getTileMap(realTileMapX, realTileMapY, posz);
    
    Tile *realTile = realTileMap->getTilePtr(realTileX, realTileY);
    
    return realTile;
    
}


Tile* WorldMap::AltGetTileAt(int posx, int posy, int posz){
    
    if( posx >= worldTileLength || posy >= worldTileLength || posz >= worldTileHeight )
        return nullptr;
    
    int realTileMapX = (posx / mapX);
    int realTileMapY = (posy / mapY);
    
    int realTileX = (posx % mapX);
    int realTileY = (posy % mapY);
    
    // I have no idea why the heightmap generator switches the X and Y positions
    // But this is the fix =shrug=
    TileMap *realTileMap = getTileMap(realTileMapY, realTileMapX, posz);
    
    Tile *realTile = realTileMap->getTilePtr(realTileX, realTileY);
    
    return realTile;
    
}