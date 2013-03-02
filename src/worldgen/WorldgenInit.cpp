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
#include "../serialization/Boost_Serialization.h"

void WorldGen::init(){
        
    TileMap *test = new TileMap(serverConfig->mapX, serverConfig->mapY);
    
    //std::string fileName(serverConfig->data_dir + "/maps/" + boost::lexical_cast<std::string>(test->getX()) + "_" + boost::lexical_cast<std::string>(test->getY()) + ".tle");
    
    std::string fileName(serverConfig->data_dir + "/maps/test.glb");
    std::ofstream ofs(fileName);
    boost::archive::binary_oarchive oarchive(ofs);
    
    oarchive << test;
    ofs.close();
    
    return;
    
}
