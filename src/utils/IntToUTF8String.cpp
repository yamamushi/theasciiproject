//
//  IntToUTF8String.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/4/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "IntToUTF8String.h"
#include <string>
#include <iostream>


std::string IntToUTF8String(int convertMe){
    
    // We only care about plane 1 right now,
    // but know that we have other options (0x10FFFF)
    // Technically UTF-8 is "limited" to 4 bytes, so it's not
    // Like it matters much anyways these days
        
    if(convertMe == 0)
        return " ";
    if( (convertMe <= 0x7F) && (convertMe > 0x00) ){
        
        std::string out(".");
        
        std::bitset<8> x(convertMe);
        
        unsigned long l = x.to_ulong();
        unsigned char c = static_cast<unsigned char>(l);
        out[0] = c;
        
        return out;
        
    } else if ( (convertMe >= 0x80) && (convertMe <= 0x07FF) ) {
        
        std::string out("..");
        
        int firstShift = (convertMe >> 0x06) ^ 0xC0;
        int secondShift = ((convertMe ^ 0xFFC0) | 0x80) & ~0x40;
        
        std::bitset<8> first(firstShift);
        std::bitset<8> last(secondShift);
        
        
        unsigned long l = first.to_ulong();
        unsigned char c = static_cast<unsigned char>(l);
        out[0] = c;
        
        unsigned long ltwo = last.to_ulong();
        unsigned char ctwo = static_cast<unsigned char>(ltwo);
        out[1] = ctwo;
        
        return out;
        
    } else if( (convertMe >= 0x0800) && (convertMe <= 0xFFFF) ){
        
        
        std::string out("...");
        
        int firstShift = ((convertMe ^ 0xFC0FFF) >> 0x0C) | 0xE0;
        int secondShift = (((convertMe ^ 0xFFF03F) >> 0x06) | 0x80) & ~0x40;
        int thirdShift = ((convertMe ^ 0xFFFC0) | 0x80) & ~0x40;
        
        std::bitset<8> first(firstShift);
        std::bitset<8> second(secondShift);
        std::bitset<8> third(thirdShift);
        
        unsigned long lone = first.to_ulong();
        unsigned char cone = static_cast<unsigned char>(lone);
        out[0] = cone;
        
        unsigned long ltwo = second.to_ulong();
        unsigned char ctwo = static_cast<unsigned char>(ltwo);
        out[1] = ctwo;
        
        unsigned long lthree = third.to_ulong();
        unsigned char cthree = static_cast<unsigned char>(lthree);
        out[2] = cthree;
        
        return out;
        
    } else{
        return " ";
    }

}