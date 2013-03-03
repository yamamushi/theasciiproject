/*
 
 WorldgenInit.cpp
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 This is where magic(tm) happens!
 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "WorldgenInit.h"
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/EntityMap.h"
#include "../mapping/WorldMap.h"
#include "../serialization/Boost_Serialization.h"

void WorldGen::init(){
        
    TileMap *test = new TileMap(serverConfig->mapX, serverConfig->mapY);
    TileMap outputMap = *test;
    
    //std::string fileName(serverConfig->data_dir + "/maps/" + boost::lexical_cast<std::string>(test->getX()) + "_" + boost::lexical_cast<std::string>(test->getY()) + ".tle");
    
    std::string fileName(serverConfig->data_dir + "/maps/test.tlm");
    std::ofstream ofs(fileName);
    boost::archive::text_oarchive oarchive(ofs);
    
    oarchive << outputMap;
    ofs.close();
    
    WorldMap *worldMap = new WorldMap(serverConfig->worldX, serverConfig->worldY, serverConfig->worldZ, serverConfig->mapX, serverConfig->mapY);
    
    std::string worldFileName(serverConfig->data_dir + "/maps/worldmap.glb");
    std::ofstream world_ofs(worldFileName);
    boost::archive::text_oarchive world_oarchive(world_ofs);
    
    world_oarchive << worldMap;
    world_ofs.close();
    
    return;
    
}
