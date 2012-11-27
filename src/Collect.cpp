/*
 * =====================================================================================
 *
 *       Filename:  Collect.cpp
 *
 *    Description:  This object defines the behavior of our "Entities", ie
 *                  The necessary functions for an entity to exist on the "Map"
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:41:29 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yamamushi (Jon Rumion)
 *   Organization:  The ASCII Project
 *
 *	  License:  GPLv3
 *
 *	  Copyright 2012 Jonathan Rumion
 *
 *   This file is part of The ASCII Project.
 *
 *   The ASCII Project is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   The ASCII Project is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with The ASCII Project.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * =====================================================================================
 */


#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "BoostLibs.h"
#include "Entities.h"
#include "ClientMap.h"
#include "Serialization.h"




int renderForPlayer(Entity *target, std::vector<char *> *outbuf, ClientMap *savedMap)
{
    
    int x, y;
    int size = 0;
    int offset, posx, posy;
    
    
    Entity tgt = *target;
    
    
    
    posx = tgt.posX();
    posy = tgt.posY();
    
    
   /* std::ofstream cofs("data/testClient.dat");
    boost::archive::binary_oarchive cia(cofs);
    cia & target->cMap;
    cofs.close(); */
    
    
    
    
   // offset = 12;
    
    for (x = posx-10; x < posx+10; x++) {
        for (y = posy-10; y < posy+10; y++) {
            if((x > 0) && (x < MAP_WIDTH) && (y > 0) && (y < MAP_HEIGHT))
           // {
                //if(tgt.returnCMap()->cMap[x][y]->sendMe)
             //   {
               //     if(savedMap->cMap[x][y]->x != tgt.returnCMap()->cMap[x][y]->x || savedMap->cMap[x][y]->y != tgt.returnCMap()->cMap[x][y]->y)
               //     {
                   // if( (savedMap->cMap[x][y]->H != tgt.returnCMap()->cMap[x][y]->H) || (savedMap->cMap[x][y]->S != tgt.returnCMap()->cMap[x][y]->S) || (savedMap->cMap[x][y]->V != tgt.returnCMap()->cMap[x][y]->V) || (savedMap->cMap[x][y]->HD != tgt.returnCMap()->cMap[x][y]->HD) || (savedMap->cMap[x][y]->SD != tgt.returnCMap()->cMap[x][y]->SD) || (savedMap->cMap[x][y]->VD != tgt.returnCMap()->cMap[x][y]->VD) || (savedMap->cMap[x][y]->ASCII != (int)*tgt.returnCMap()->cMap[x][y]->symbol) || (savedMap->cMap[x][y]->visible != tgt.returnCMap()->cMap[x][y]->visible) || (savedMap->cMap[x][y]->blocked != tgt.returnCMap()->cMap[x][y]->blocked) || (savedMap->cMap[x][y]->occupied != tgt.returnCMap()->cMap[x][y]->occupied) )
                    {
                       // tgt.returnCMap()->cMap[x][y]->x = savedMap->cMap[x][y]->x;
                       // tgt.returnCMap()->cMap[x][y]->y = savedMap->cMap[x][y]->y;
                        
                        //tgt.returnCMap()->cMap[x][y]->sendMe = false;
                        
                        
                        ClientMapPacker *packer = new ClientMapPacker();
                        char *buf = new char[TILE_PACKET_SIZE];
                        memset(buf, '.', TILE_PACKET_SIZE);
                        
                        
                        packer->packToNet( *tgt.returnCMap()->cMap[x][y], (unsigned char*)buf);
                        
                        outbuf->push_back(buf);
                        size++;
                        delete packer;
                    }
                    
              //      }
             //   }
           // }
            
        }
    }
    
    if(size == 0)
    {
       
        
        ClientMapPacker *packer = new ClientMapPacker();
        char *buf = new char[TILE_PACKET_SIZE];
        memset(buf, '.', TILE_PACKET_SIZE);
        
        
        packer->packToNet( *tgt.returnCMap()->cMap[posx][posy], (unsigned char*)buf);
        
        outbuf->push_back(buf);
        size++;
        delete packer;
    }
    
    return size;
}

