#include "Headers.h"






void WorldMap::initWorldMap()
{
    
    for(int x = 0; x < wX; x++)
    {
        for(int y = 0; y < wY; y++)
        {            
            for(int z = 0; z < wZ; z++)
            {
              //  cout << x << " " << y << " " << z << endl;
                //eMap[x][y][z].push_back(new EntityMap(MAP_WIDTH, MAP_HEIGHT, tMap->at(x).at(y).at(z)) );
              //  tMap->at(x).at(y).at(z)->
                //push_back(new TileMap(MAP_WIDTH,MAP_HEIGHT));
                
                eMap->at(x).at(y).at(z) = new EntityMap(MAP_WIDTH, MAP_HEIGHT, tMap->at(x).at(y).at(z) );
                
            }
        }
    }
    
}




