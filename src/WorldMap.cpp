#include "Headers.h"






void WorldMap::initWorldMap()
{
    
    for(int x = 0; x < wX; x++)
    {
        for(int y = 0; y < wY; y++)
        {            
            for(int z = 0; z < wZ; z++)
            {

                eMap->at(x).at(y).at(z) = new EntityMap(MAP_WIDTH, MAP_HEIGHT, new TileMap(MAP_WIDTH, MAP_HEIGHT) );
                
            }
        }
    }
        
}



void WorldMap::addEntToCenter(Entity *tgt)
{
   
    tgt->setWorldPosition(cX, cY, cZ-1);
    eMap->at(cX).at(cY).at(cZ-1)->addToMap(tgt);
    
    
}


void WorldMap::removeEnt(Entity *tgt)
{
    int tX, tY, tZ;
    tX = tgt->wX;
    tY = tgt->wY;
    tZ = tgt->wZ;
    
    eMap->at(tX).at(tY).at(tZ)->removeFromEntMap(tgt);
    
}



void WorldMap::moveEnt(Entity *tgt, int x, int y)
{
    
    bool moved = tgt->move(x, y);
    
    int oldx, oldy, tWX, tWY, tWZ;
    oldx = tgt->posX();
    oldy = tgt->posY();
    
    tWX = tgt->wX;
    tWY = tgt->wY;
    tWZ = tgt->wZ;
    
    
    
    
    if(!moved && oldx+x <= 0)
    {
        if(tWX == 0)
            tWX = wX;
        
        moveEntTo(tgt, tWX-1, tWY, tWZ, MAP_WIDTH-1, oldy);
        return;
    }
    else if(!moved && oldx+x >= MAP_WIDTH)
    {
        if(tWX == wX-1)
            tWX = -1;
        
        moveEntTo(tgt, tWX+1, tWY, tWZ, 1, oldy);
        return;
    }
    else if(!moved && oldy+y <= 0)
    {
        if(tWY == 0)
            tWY = wY;
        
        moveEntTo(tgt, tWX, tWY-1, tWZ, oldx, MAP_HEIGHT-1);
        return;
    }
    else if(!moved && oldy+y >= MAP_HEIGHT)
    {
        if(tWY == wY-1)
            tWY = -1;
        
        moveEntTo(tgt, tWX, tWY+1, tWZ, oldx, 1);
        return;
    }
}


void WorldMap::moveEntTo(Entity *tgt, int x, int y, int z, int px, int py)
{
    
    
    eMap->at(tgt->wX).at(tgt->wY).at(tgt->wZ)->removeFromEntMap(tgt);
    
    tgt->setWorldPosition(x, y, z);
    eMap->at(x).at(y).at(z)->addToMapAt(tgt, px, py);
    
    
    
}
















