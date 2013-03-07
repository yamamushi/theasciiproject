#pragma once
//
//  WorldErosion.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/3/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "WorldDrawing.h"
#include "../mapping/WorldMap.h"
#include "../mapping/TileMap.h"
#include "../mapping/Tile.h"
#include "../mapping/GeometryFunctions.h"
#include "../parsers/ServerConfig.h"
#include "../utils/FileLogger.h"
#include "../utils/Random.h"

#include <memory>


class WorldErosion {
    
private:
    
    std::shared_ptr<WorldMap> worldMap;
    std::shared_ptr<ServerConfigParser> serverConfig;
    std::shared_ptr<Random> randomGen;
    
    void run();
    void TileMapErode(TileMap *input, int heightRange);
    void WorldMapErode(WorldMap *input, int heightRange);
    
public:
    
    WorldErosion(std::shared_ptr<WorldMap> world, std::shared_ptr<ServerConfigParser> config) : worldMap(world), serverConfig(config){run();};
    
    
    
};
