/*
 * =====================================================================================
 *
 *       Filename:  Tiles.h
 *
 *    Description:  This object defines the behavior of all Tiles, ie
 *                  Necessary functions in order for our world to operate.
 *
 *        Version:  1.0
 *        Created:  07/03/2012 07:50:52 AM
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



class Tile {
private:
    
    unsigned int TypeID, SubTypeID;
    
public:
    int posX, posY;
    float H, S, V, HD, SD, VD;
    int R, G, B, RD, GD, BD;
    wchar_t *symbol;
    
    bool blocked;
    bool block_sight;
    bool visible;
    bool explored;
    bool occupied;
    bool needsOrientation;
    
    
    
    Tile(bool blked=true);
    void init_Tile(bool);
    virtual ~Tile() {}
    
    bool isSightBlocked();
    bool isBlocked();
    bool isVisible();
    bool isExplored();
    
    void setHSV(float h, float s, float v);
    void setSymbol(wchar_t *ch);
    wchar_t *getSymbol();
    
    void setTypeID(int i);
    void setSubTypeID(int i);
    unsigned int getTypeID();
    unsigned int getSubTypeID();
    
    // Some nasty stuff I don't like doing...
    virtual void setOrientation(int i)=0;
    
    
    
    friend class TileMap;
};


class Wall : public Tile {
    
private:
    wchar_t *orient[16];
    
    
public:
    Wall(bool blked=true);
    virtual void setOrientation(int i);
    
    
    
};


class Floor : public Tile {
private:
    
public:
    Floor(bool blked=false);
    virtual void setOrientation(int i);
    
    
};


class Slope : public Tile {
    
private:
    
public:
    Slope(bool blked=false);
    virtual void setOrientation(int i);
};


class Air : public Tile
{
    
    
private:
    
public:
    
    Air(bool blked=false);
    virtual void setOrientation(int i);
};




class Rect {
private:
    
public:
    int x1, y1, x2, y2, cX, cY;
    Rect(int, int, int, int);
    void initRect(int, int, int, int);
};


class Room {
private:
    
public:
    int cX, cY;
    int x1, x2, y1, y2;
    Room(int, int, int, int);
    void initRoom(int, int, int, int);
    bool doesBorder(Room *other);
    bool doesContainPoint(int, int);
    bool doesIntersect(Room *other);
    
    friend class TileMap;
    
};


class Hall {
private:
    
public:
    int x1, x2, y, dir;
    Hall(int, int, int, int);
    void initHall(int, int, int, int);
    
};







