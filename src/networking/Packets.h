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

// This packet type can be used to send specific Tile ID's to clients
// Probably shouldn't use this when sending large amounts of data
// However single tile updates would benefit from this.

typedef struct {
    
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & TileID;
    }
    
    int TileID;
    
} TilePacket;


// We can use the MapPacket to send an entire chunk of map updates at once
// Unfortunately we're left with a larger packet that we need due to the
// Serialization overhead

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
    std::vector< std::vector<std::string > > symbolTable;
    
} MapPacket;


// Header Packet
// Tells us the size of the next incoming packet of data,
// And the type of data we are receiving from the server.

typedef struct {
    
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & HeaderSize;
        ar & API_ID;
    }
    
    unsigned int HeaderSize;
    int API_ID;
    
} HeaderPacket;


/// The size of a fixed length header.
enum { HEADER_SIZE = 8 };