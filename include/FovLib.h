/*
 * =====================================================================================
 *
 *       Filename:  FovLib.h
 *
 *    Description:  This library handles FOV calculations for entities.
 *
 *        Version:  1.0
 *        Created:  07/19/2012 07:42:29 PM
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

class ClientMap;
class TileMap;
class Entity;
class EntityMap;
class TCODMap;

class FovLib {

private:
    TCODMap *tcodMap;
    TileMap *tileMap;
    
    ClientMap *cMap;

public:

    FovLib(TileMap *map);
    void initFovLib(TileMap *map);

    void refreshFov(Entity *tgt, int radius);
    void refreshFov(Entity *tgt, int X, int Y, int radius);
    
    
    void refreshFov(EntityMap *tgt, int X, int Y, int radius);

    TileMap * getTileMap();


};
