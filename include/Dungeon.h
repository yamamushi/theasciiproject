/*
 * =====================================================================================
 *
 *       Filename:  Dungeon.h
 *
 *    Description:  Our dungeon generator
 *
 *        Version:  1.0
 *        Created:  07/05/2012
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

class TileMap;
class Room;

class Dungeon {
    
private:
    TileMap *destMap;
    TileMap *dungeonMap;
    
    Room *tempRoom;
    int x, w, h, y, i;
    
public:
    Dungeon(TileMap *destination, int width, int height, bool create);
    void initDungeon(TileMap *destination,int width,int height, bool create);
    bool createRooms(int numberOfRooms, int minSize, int maxSize, TileMap *outputMap);
    
    void connectRooms(TileMap *outputMap);
    
    
    
};
