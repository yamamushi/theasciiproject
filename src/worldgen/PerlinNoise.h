#pragma once
//
//  PerlinNoise.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/6/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "../mapping/Tile.h"
#include "../mapping/TileMap.h"
#include "../mapping/WorldMap.h"

inline double FindPerlinNoise(double x);
inline double FindPerlinNoise(double x,double y);
inline double InterpolatePerlin(double a,double b,double x);

void TileNoiseHeightmap(TileMap *tileMap, double zoom, double persistence, double range, int octaves=2);
