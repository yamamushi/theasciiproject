//
//  WorldErosion.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/3/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "WorldDrawing.h"
#include "WorldErosion.h"
#include "PerlinNoise.h"
#include "SimplexNoise.h"
#include "../mapping/GeometryFunctions.h"
#include "../utils/Random.h"
#include "../utils/FileLogger.h"
#include "../utils/IntToUTF8String.h"
#include <cmath>
#include <memory>
#include <string>
#include <sstream>
#include <codecvt>

#include <iostream>

extern FileLogger *fileLogger;


void WorldErosion::run(){
    
    std::shared_ptr<Random> randomGen(new Random());
    
    //TileMap *testErode = worldMap->getTileMap(randomGen->rand_crypt(serverConfig->worldX)-1, randomGen->rand_crypt(serverConfig->worldY)-1, randomGen->rand_crypt(serverConfig->worldZ)-1);
    
    
    /*  fileLogger->WorldLog("WorldMap Erosion Started");
     for(int x = 0; x < worldMap->getX(); x++){
     for(int y = 0; y < worldMap->getY(); y++){
     for(int z = 0; z < worldMap->getZ(); z++){
     
     TileMap *testErode = worldMap->getTileMap(x, y, z);
     if(testErode == nullptr)
     break;
     TileMapErode(testErode);
     
     }
     }
     }
     fileLogger->WorldLog("WorldMap Erosion Completed"); */
    
    // Bresenham3D(5, 5, 0, 5, 5, 5, worldMap.get(), " ");
    
    //TileNoiseHeightmap(worldMap->getTileMap(0, 0, 0), 16, 0.50, 256, 2);
    //TileMapErode(worldMap->getTileMap(0, 0, 0), 30);
    WorldMapHeightMap(worldMap.get(), 32, 0.50, 128, 2);
    
    
}


void WorldErosion::TileMapErode(TileMap *input, int heightRange){
    
    int mapWidth = input->getWidth();
    int mapHeight = input->getLength();
    
    
    for( int x=0; x < mapWidth; x++){
        for( int y=0; y < mapHeight; y++){
            
            // Useless function at the moment, a placeholder I suppose
            
        }
    }
    
}