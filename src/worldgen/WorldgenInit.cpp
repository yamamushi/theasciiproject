/*
 
 WorldgenInit.cpp
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 This is where magic(tm) happens!
 
 */

#include "../serialization/Boost_Serialization.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "WorldgenInit.h"
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/EntityMap.h"
#include "../mapping/WorldMap.h"
#include "../utils/FileLogger.h"

extern FileLogger *fileLogger;

void WorldGen::init(){
    
    fileLogger->ErrorLog("WorldGen Started");
    
    fileLogger->ErrorLog("Creating World Structure");
    std::shared_ptr<WorldMap> worldMap(new WorldMap(serverConfig->worldX, serverConfig->worldY, serverConfig->worldZ, serverConfig->mapX, serverConfig->mapY));
    fileLogger->ErrorLog("World Structure Generated");
    
    fileLogger->ErrorLog("Saving World to Disk");
    std::string worldFileName(serverConfig->data_dir + "/maps/worldmap.glb");
    std::ofstream world_ofs(worldFileName);
    boost::archive::text_oarchive world_oarchive(world_ofs);
    
    WorldMap *worldMapOut = worldMap.get();
    world_oarchive << worldMapOut;
    world_ofs.close();
    fileLogger->ErrorLog("World Saved to Disk at " + worldFileName);
    
    return;
    
}


