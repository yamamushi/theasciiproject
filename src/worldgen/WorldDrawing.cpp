//
//  WorldDrawing.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "WorldDrawing.h"
#include "Bresenham.h"
#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/WorldMap.h"
#include "../mapping/GeometryFunctions.h"
#include "../utils/FileLogger.h"




void drawLineOnTileMap(int x1, int y1, int x2, int y2, TileMap *output, int symbol){
    Bresenham2D(x1, y1, x2, y2, output, symbol);
}



void drawLineOnWorldMap(int x1, int y1, int z1, int x2, int y2, int z2, WorldMap *output, int symbol){
    Bresenham3D(x1, y1, z1, x2, y2, z2, output, symbol);
}

