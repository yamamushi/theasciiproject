//
//  Display.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#include "Display.h"
#include "UnicodeConstants.h"


Display::Display(int x, int y){
    
    Width = x;
    Height = y;
    
   
    MainWindow = new Window(Width, Height, true);
    
}


Display::~Display(){
    
    DisplayLines.clear();
    
    
}


std::string Display::returnDisplay(){
    
    std::string display;
    
    for(int x = 0; x < Height; x++)
    {
        display.append(MainWindow->returnWindowLine(x));
        
    }
    
    return display;
    
}