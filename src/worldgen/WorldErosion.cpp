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
    
    //TileNoiseHeightmap(worldMap->getTileMap(0, 0, 0), 5.8, 0.75, 8.0);
    TileMapErode(worldMap->getTileMap(0, 0, 0), 255.0);

}


void WorldErosion::TileMapErode(TileMap *input, int heightRange){
    
    int mapWidth = input->getWidth();
    int mapHeight = input->getLength();
    double pi = 3.14;
    
    // The x1,y1,x2,y2 seems to be some sort of scaling, the larger distance, the detailed noise. if this helps anyone.
    double x1 = 0;
    double x2 = .5;
    double y1 = .2;
    double y2 = .8;
    
    for( int x=0; x < mapWidth; x++){
        for( int y=0; y < mapHeight; y++){
            
            double s=x/mapWidth;
            double t=y/mapHeight;
            double dx=x2-x1;
            double dy=y2-y1;
            
            double nx=(x1+cos(s*2*pi))*(dx/(2*pi));
            double ny=(y1+cos(t*2*pi))*(dy/(2*pi));
            double nz=(x1+sin(s*2*pi))*(dx/(2*pi));
            double nw=(y1+sin(t*2*pi))*(dy/(2*pi));
            
            //double getnoise = raw_noise_4d(nx,ny,nz,nw);
            //int heightMap = (int)((getnoise*(heightRange/2))+(heightRange/2));
            
            double getnoise = scaled_raw_noise_4d(0, heightRange, nx, ny, nz, nw);
            int heightMap = (int)getnoise;
            
            if(heightMap>heightRange)
                heightMap = heightRange;
            if(heightMap<0)
                heightMap = 0;
            
            //heightMap = heightMap + 0x2581;
            
            //input->getTilePtr(x, y)->setSymbol(IntToUTF8String(heightMap));
            input->getTilePtr(x, y)->setSymbol(std::to_string(heightMap));
            
        }
    }
    
}