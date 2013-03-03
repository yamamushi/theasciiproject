//
//  WorldEngine.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/2/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//
//  This engine runs and keeps track of information in our game world.
//  Calls for information from the game world pass through this engine.
//  Calls to update game world information are done through this engine.
//  Calls to update entity objects are done through this engine, however remember
//  that the AI behind those entities are not handled in this engine.
//

#include "../mapping/WorldMap.h"
#include <memory>


class WorldEngine {
  
private:
    
    std::shared_ptr<WorldMap> worldMap;
    
public:
    
    WorldEngine(std::shared_ptr<WorldMap> wMap) : worldMap(wMap){};
    ~WorldEngine(){};
    
    void init();
    
};