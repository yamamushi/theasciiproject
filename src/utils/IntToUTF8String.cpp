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
#include <clocale>
#include <locale>
#include <vector>
#include <codecvt>
#include <sstream>
#include <cstdio>
#include <boost/format.hpp>


// This needs to be completed.

std::string IntToUTF8String(int convertMe){
    
    // We only care about plane 1 right now,
    // but know that we have other options (0x10FFFF)
    
    // convertMe = 0x263A;
    
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
        
        int firstShift = (convertMe >> 0x6) ^ 0xC0;
        int secondShift = (convertMe ^ 0xFFC0) | 0x80;
        
        std::bitset<8> first(firstShift);
        std::bitset<8> last(secondShift);
        last.set(6, false);
        
        
        unsigned long l = first.to_ulong();
        unsigned char c = static_cast<unsigned char>(l);
        out[0] = c;
        
        unsigned long ltwo = last.to_ulong();
        unsigned char ctwo = static_cast<unsigned char>(ltwo);
        out[1] = ctwo;
        
        return out;
        
    } else if( (convertMe >= 0x0800) && (convertMe <= 0xFFFF) ){
        
        
        std::string out("...");
        
        int firstShift = ((convertMe ^ 0xFC0FFF) >> 0xC) | 0xE0;
        int secondShift = ((convertMe ^ 0xFFF03F) >> 0x6) | 0x80;
        int thirdShift = (convertMe ^ 0xFFFC0) | 0x80;
        
        std::bitset<8> first(firstShift);
        std::bitset<8> second(secondShift);
        second.set(6, false);
        std::bitset<8> third(thirdShift);
        third.set(6, false);
        
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