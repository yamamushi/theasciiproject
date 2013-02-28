/*
 
 WorldgenInit.h
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 This object pulls in our worldgen settings, holds various important
 pieces of information pertinent to getting our world up and running
 by itself, and eventually releases the world....
 
 */


#include "../mapping/Tile.h"
#include "../mapping/EntityMap.h"
#include "../parsers/ServerConfig.h"


class WorldGen {
    
private:
    
    int worldX;
    int worldY;
    int worldZ;
    
    int mapX, mapY;
    
    ServerConfigParser *serverConfig;
    
public:
    
    WorldGen(ServerConfigParser *config) : serverConfig(config), mapX(config->mapX), mapY(config->mapY), worldX(config->worldX), worldY(config->worldY), worldZ(config->worldZ){};
    
    void init();
    
    virtual ~WorldGen(){};
    
};
