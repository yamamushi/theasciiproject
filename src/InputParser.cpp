/*
 * =====================================================================================
 *
 *       Filename:  InputParser.cpp
 *
 *    Description:  This class handles the parsing of raw input sent from clients to the server.
 *
 *        Version:  1.0
 *        Created:  11/19/2012 01:22:29 AM
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
#include <iostream>
#include <fstream>


#include "Entities.h"
#include "EntityMap.h"
#include "WorldMap.h"
#include "TileMap.h"
#include "InputParser.h"


InputParser::InputParser(Entity *Player){
    
    player = Player;
    
    
}



std::string InputParser::parse(std::string command){
    
   
    if( command == "getPos" || command == "getpos")
    {
        std::string playerPos(player->posX() + " " + player->posY());
        
        return playerPos;
        
    }
    else if(command == "dumpMap" || command == "dumpmap")
    {
        extern WorldMap *worldMap;
        worldMap->backupToDisk();

        std::string success("Map Written To Disk");
        return success;
    }
    else if( command == "time")
    {
        time_t rawtime;
        
        struct tm * timeinfo;
        time( &rawtime ); 
        timeinfo = localtime(&rawtime);
        
        std::string time = asctime(timeinfo);
        

        return time;
    }
    else
    {
        std::string tmp("");
        return tmp;
    }
 
    
}





void InputParser::handleAPI(int api)
{
    
    // We start off by mapping our numpad keys
    // To movement directions
    extern WorldMap *worldMap;
    
    if ( api == 0)
    {
        worldMap->moveEnt(player, 0, 0);
    }
    else if ( api == 1)
    {
        //player->move(-1, 1);
        worldMap->moveEnt(player, -1, 1);
    }
    else if ( api == 11)
    {
        player->removeWall(-1, 1);
    }
    else if ( api == 21)
    {
        player->placeWall(-1, 1);
    }
    else if ( api == 31)
    {
        player->placeFloor(-1, 1);
    }
    else if ( api == 41)
    {
        player->digHole(-1, 1);
    }
    
    
    else if ( api == 2)
    {
        //player->move(0, 1);
        worldMap->moveEnt(player, 0, 1);
    }
    else if ( api == 12)
    {
        player->removeWall(0, 1);
    }
    else if ( api == 22)
    {
        player->placeWall(0, 1);
    }
    else if ( api == 32)
    {
        player->placeFloor(0, 1);
    }
    else if ( api == 42)
    {
        player->digHole(0, 1);
    }
    
    
    
    else if ( api == 3)
    {
        //player->move(1, 1);
        worldMap->moveEnt(player, 1, 1);
    }
    else if ( api == 13)
    {
        player->removeWall(1, 1);
    }
    else if ( api == 23)
    {
        player->placeWall(1, 1);
    }
    else if ( api == 33)
    {
        player->placeFloor(1, 1);
    }
    else if ( api == 43)
    {
        player->digHole(1, 1);
    }
    
    
    
    else if (api == 4)
    {
        //player->move(-1, 0);
        worldMap->moveEnt(player, -1, 0);
    }
    else if ( api == 14)
    {
        player->removeWall(-1, 0);
    }
    else if ( api == 24)
    {
        player->placeWall(-1, 0);
    }
    else if ( api == 34)
    {
        player->placeFloor(-1, 0);
    }
    else if ( api == 44)
    {
        player->digHole(-1, 0);
    }
    
    
    
    else if (api == 5)
    {
        worldMap->changEntZ(player, 1);
    }
    
    
    else if ( api == 15)
    {
        worldMap->changEntZ(player, -1);
    }
    
    else if ( api == 25)
    {
        player->digUp();
    }
    
    else if ( api == 35)
    {
        player->digDown();
    }
    
    
    else if (api == 6)
    {
        //player->move(1, 0);
        worldMap->moveEnt(player, 1, 0);
    }
    else if ( api == 16)
    {
        player->removeWall(1, 0);
    }
    else if ( api == 26)
    {
        player->placeWall(1, 0);
    }
    else if ( api == 36)
    {
        player->placeFloor(1, 0);
    }
    else if ( api == 46)
    {
        player->digHole(1, 0);
    }
    
    
    
    else if (api == 7)
    {
        //player->move(-1, -1);
        worldMap->moveEnt(player, -1, -1);
    }
    else if ( api == 17)
    {
        player->removeWall(-1, -1);
    }
    else if ( api == 27)
    {
        player->placeWall(-1, -1);
    }
    else if ( api == 37)
    {
        player->placeFloor(-1, -1);
    }
    else if ( api == 47)
    {
        player->digHole(-1, -1);
    }
    
    
    
    else if (api == 8)
    {
        //player->move(0, -1);
        worldMap->moveEnt(player, 0, -1);
    }
    else if ( api == 18)
    {
        player->removeWall(0, -1);
    }
    else if ( api == 28)
    {
        player->placeWall(0, -1);
    }
    else if ( api == 38)
    {
        player->placeFloor(0, -1);
    }
    else if ( api == 48)
    {
        player->digHole(0, -1);
    }
    
    
    
    else if (api == 9)
    {
        //player->move(1, -1);
        worldMap->moveEnt(player, 1, -1);
    }
    else if ( api == 19)
    {
        player->removeWall(1, -1);
    }
    else if ( api == 29)
    {
        player->placeWall(1, -1);
    }
    else if ( api == 39)
    {
        player->placeFloor(1, -1);
    }
    else if ( api == 49)
    {
        player->digHole(1, -1);
    }
    
}






