#pragma once
/*
 * =====================================================================================
 *
 *       Filename:  InputParser.cpp
 *
 *    Description:  InputParser Class Definition
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


class Entity;
class EntityMap;
class WorldMap;
class TileMap;




class InputParser {
    
private:
    
    Entity *player;
    
    
public:
    
    InputParser(Entity *Player);
    virtual ~InputParser(){};


    std::string parse(std::string command);
    void handleAPI(int api);


};




