//
//  Keyboard.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/16/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#include "Keyboard.h"

#include <iostream>
#include <string>
#include "Display.h"



Keyboard::Keyboard(Display *attachTo){
    
    attachedDisplay = attachTo;
    
}



int Keyboard::parseKey(std::string input){
    

    if(input == "a"){
        std::cout << "a" << std::endl;
        return KEY_a;
    }
    else if(input == "\x1b[A"){
        std::cout << "up" << std::endl;
        return KEY_UP;
    }
    else if(input == ""){
        std::cout << "none" << std::endl;
    }
    
    
    
    else{
        return KEY_NONE;
    }
}
    

