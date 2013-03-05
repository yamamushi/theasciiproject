//
//  WorldDrawing.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "WorldDrawing.h"
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/WorldMap.h"
#include "../mapping/GeometryFunctions.h"
#include "../utils/FileLogger.h"

#include <string>
#include <algorithm>



void drawLineOnTileMap(int x1, int y1, int x2, int y2, TileMap *output, std::string symbol){
    
    int minX, minY;
    int maxX, maxY;
    
    minX = std::min(x1, x2);
    minY = std::min(y1, y2);
    maxX = std::max(x1, x2);
    maxY = std::max(x1, x2);
    
    for(int startX = minX; startX < maxX; startX++){
        for( int startY = minY; startY < maxY; startY++){
            
            if(IsPointOnLine(x1, y1, x2, y2, startX, startY)){
             
                Tile *updateTile = output->getTilePtr(startX, startY);
                updateTile->setSymbol(symbol);
                
            }
        }
    }
    
    
}