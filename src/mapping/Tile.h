#pragma once
/*
 
 Tile.h
 2-24-2013
 
 -Jon Rumion (Yamamushi@gmail.com)
 
 
 This is going to be the source of a lot of headaches.
 
 */

#include "../serialization/Boost_Serialization.h"
#include "../utils/IntToUTF8String.h"
#include <boost/shared_ptr.hpp>
#include <string>

class Tile {
    
private:
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //ar & posX;
        //ar & posY;
        ar & symbol;
    }
    
    //int posX, posY;
    //std::string symbol;
    int symbol;
    
public:
    Tile(){};
    //Tile(int PosX, int PosY, const char *Symbol) : posX(PosX), posY(PosY), symbol(Symbol){};
    Tile(int Symbol) : symbol(Symbol){};
    
    //int getX(){return posX;};
    //int getY(){return posY;};
    //void setX(int x){posX = x;};
    //void setY(int y){posY = y;};
    //void setSymbol(std::string sym){symbol = sym;};
    void setSymbol(int sym){symbol = sym;};
    std::string getSymbol(){return IntToUTF8String(symbol);}
    
    virtual ~Tile(){};
    
};

BOOST_SERIALIZATION_SHARED_PTR(Tile)

