#pragma once
//
//  WorldDrawing.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//


#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/WorldMap.h"
#include "../utils/FileLogger.h"

#include <string>

void drawLineOnTileMap(int x1, int y1, int x2, int y2, TileMap *output, std::string symbol);
void drawLineOnWorldMap(int x1, int y1, int z1, int x2, int y2, int z2, WorldMap *output, std::string symbol);
void Bresenham2D(int x1, int y1, int const x2, int const y2, TileMap *output, std::string symbol);
void Bresenham3D(int x1, int y1, int z1, const int x2, const int y2, const int z2, WorldMap *output, std::string symbol);