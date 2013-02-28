#pragma once
//
//  WorldMap.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 2/28/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//


class WorldMap {
  
private:
    
    int X,Y,Z;
    
public:
    
    WorldMap( int x, int y, int z) : X(x), Y(y), Z(z){};
    
    ~WorldMap(){};
    
};
