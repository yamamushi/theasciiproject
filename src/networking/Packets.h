#pragma once
//
//  Packets.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//


#include "Packets.h"
#include "../serialization/Boost_Serialization.h"
#include <vector>
#include <string>


typedef struct {
    
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & TileID;
    }
    
    int TileID;
    
} TilePacket;


typedef struct {
    
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & length;
        ar & width;
        ar & symbolTable;
    }
    
    int length;
    int width;
    std::vector< std::vector<std::wstring > > symbolTable;
    
} MapPacket;


typedef struct {
    
    int HeaderSize;
    int API_ID;
    
} HeaderPacket;