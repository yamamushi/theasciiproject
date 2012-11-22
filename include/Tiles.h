#ifndef TILES_H_
#define TILES_H_

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

#include "BoostLibs.h"




class Tile {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & wSymbol;
        ar & posX;
        ar & posY;
        ar & blocked;
        ar & block_sight;
        ar & visible;
        ar & H;
        ar & S;
        ar & V;
        ar & HD;
        ar & SD;
        ar & VD;
    }
    
    unsigned int TypeID, SubTypeID;
    
public:
    int posX, posY;
    float H, S, V, HD, SD, VD;
    int R, G, B, RD, GD, BD;
    std::wstring wSymbol;
    wchar_t *symbol;
    
    bool blocked;
    bool block_sight;
    bool visible;
    bool explored;
    bool occupied;
    bool needsOrientation;
    bool isLit;
    
    // this mess of an initializer ... sigh..
    Tile(std::wstring symbol_, int posX_, int posY_, bool blocked_, bool block_sight_, bool visible_, float H_, float S_, float V_, float HD_, float SD_, float VD_ ) : posX(posX_), posY(posY_), blocked(blocked_), block_sight(block_sight_), visible(visible_), H(H_), S(S_), V(V_), HD(HD_), SD(SD_), VD(VD_){ symbol = (wchar_t *)wSymbol.c_str();};
    Tile(bool blked=false);
    void init_Tile(bool);
    virtual ~Tile() {}
    
    bool isSightBlocked();
    bool isBlocked();
    bool isVisible();
    bool isExplored();
    
    void setHSV(float h, float s, float v, bool dark=false);
        
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
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Tile>(*this);
    }
    
    
public:
    Wall(bool blked=true);
    virtual void setOrientation(int i);
    
    
    
};




class solidEarth : public Tile {
    
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Tile>(*this);
    }
       
    
public:
    solidEarth(bool blked=true);
    virtual void setOrientation(int i);
 
};



class Floor : public Tile {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Tile>(*this);
    }
    
public:
    Floor(bool blked=true);
    virtual void setOrientation(int i);
    
    
};


class Slope : public Tile {
    
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Tile>(*this);
    }
    
public:
    Slope(bool blked=false);
    virtual void setOrientation(int i);
};


class Air : public Tile
{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Tile>(*this);
    }
    
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
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & cX;
        ar & cY;
        ar & x1;
        ar & x2;
        ar & y1;
        ar & y2;
    }
    
public:
    int cX, cY;
    int x1, x2, y1, y2;
    Room(){};
    Room(int, int, int, int);
    void initRoom(int, int, int, int);
    bool doesBorder(Room *other);
    bool doesContainPoint(int, int);
    bool doesIntersect(Room *other);
    
    friend class TileMap;
    
};


class Hall {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & x1;
        ar & x2;
        ar & y;
        ar & dir;
    }
    
public:
    int x1, x2, y, dir;
    Hall(){};
    Hall(int, int, int, int);
    void initHall(int, int, int, int);
    
};


// sigh, someone shoot me
// I hate having to put these exports down here
// But this is how they say it has to be... :(

BOOST_CLASS_TRACKING(Tile, boost::serialization::track_always);
BOOST_CLASS_TRACKING(Floor, boost::serialization::track_selectively);
BOOST_CLASS_TRACKING(Wall, boost::serialization::track_never);
BOOST_CLASS_TRACKING(solidEarth, boost::serialization::track_never);
BOOST_CLASS_TRACKING(Air, boost::serialization::track_never);
BOOST_CLASS_TRACKING(Slope, boost::serialization::track_never);


#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_KEY(Tile);
BOOST_CLASS_EXPORT_KEY(Floor);
BOOST_CLASS_EXPORT_KEY(Wall);
BOOST_CLASS_EXPORT_KEY(solidEarth);
BOOST_CLASS_EXPORT_KEY(Air);
BOOST_CLASS_EXPORT_KEY(Slope);
BOOST_CLASS_EXPORT_KEY(Room);
BOOST_CLASS_EXPORT_KEY(Hall);



#endif

