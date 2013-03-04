//
//  WorldErosion.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/3/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "WorldErosion.h"
#include "../utils/Random.h"
#include "../utils/FileLogger.h"
#include "../utils/IntToUTF8String.h"
#include <memory>
#include <string>
#include <sstream>
#include <codecvt>



extern FileLogger *fileLogger;


void WorldErosion::run(){
    
    std::shared_ptr<Random> randomGen(new Random());
    
    //TileMap *testErode = worldMap->getTileMap(randomGen->rand_crypt(serverConfig->worldX)-1, randomGen->rand_crypt(serverConfig->worldY)-1, randomGen->rand_crypt(serverConfig->worldZ)-1);
    
    TileMap *testErode = worldMap->getTileMap(1, 1, 1);
    
    fileLogger->WorldLog("TileMapErod Started");
    TileMapErode(testErode);
    fileLogger->WorldLog("TileMapErod Completed");

}


void WorldErosion::TileMapErode(TileMap *input){
    
    int count = randomGen->rand_crypt(input->getWidth()*input->getLength());
    
    for( int x=0; x<count; x++){
        
        int posX, posY;
        posX = randomGen->rand_crypt(input->getLength())-1;
        posY = randomGen->rand_crypt(input->getWidth())-1;
        
        int symInt = randomGen->rand_crypt_range(9472, 9599);
        
        Tile *tileUpdate = input->getTilePtr(posX, posY);
        
        std::string symbol = IntToUTF8String(symInt);
        
        tileUpdate->setSymbol(symbol);
        
    }
    
}