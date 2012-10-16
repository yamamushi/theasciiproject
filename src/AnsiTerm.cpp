//
//  AnsiTerm.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#include <string>
#include <sstream>

#include "AnsiTerm.h"


std::string returnLineFormat(int y){
    
    std::string output, count;
    std::stringstream line;
    
    line << y;

    count = line.str();
    
    output = "\x1b[1H";
    output.replace(2, 1, count);
    
    return output;
}


std::string returnColumnFormat(int x){
    
    std::string output, count;
    std::stringstream line;
    
    line << x;
    
    count = line.str();
    
    output = "\x1b[1G";
    output.replace(2, 1, count);
    
    return output;
    
    
}

std::string returnPosFormat(int x, int y){
    
    std::string line, column, output;
    line = returnLineFormat(y);
    column = returnColumnFormat(x);
    
    output = line + column;
    
    return output;
}