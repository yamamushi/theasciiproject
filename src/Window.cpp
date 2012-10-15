//
//  Window.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//


#include <sstream>

#include "Window.h"
#include "UnicodeConstants.h"



Window::Window(int x, int y, bool bordered){
    
    Width = x;
    Height = y;
    
    
    if(bordered)
    {
        std::string topbar, bottombar, endcount;
        std::stringstream end, bottomend;
        end << Width;
        endcount = end.str();
        std::string tmp("\x1b[1G");
        tmp.replace(2, 1, endcount);
        
        topbar = "\x1b[2J\x1b[1H";
        topbar.append(TopLeftThinCorner);
        for(int x=0; x < Width-2; x++)
        {
            topbar.append(HorizontalThinBoxLine);
        }
        topbar.append(tmp);
        topbar.append(TopRightThinCorner);
        
        
        WindowLines.push_back(topbar);
        
        for(int x=2; x < Height; x++)
        {
            
            std::string begincount;
            std::stringstream begin;
            
            begin << x;            
            begincount = begin.str();            
            
            std::string line("\x1b[1H");
            line.replace(2, 1, begincount);
            line.append(VerticalThinBoxLine);
            
            std::string endline("\x1b[1G");
            endline.replace(2, 1, endcount);
            endline.append(VerticalThinBoxLine);
            
            line.append(endline);
            
            WindowLines.push_back(line);
            
        }
    
        std::string bottomendcount;
        std::string bottomcount("\x1b[1H");
        bottomend << Height;
        
        bottomendcount = bottomend.str();
        bottomcount.replace(2, 1, bottomendcount);
        bottomcount.append(BottomLeftThinCorner);
        for(int x=0; x < Width-2; x++)
        {
            bottomcount.append(HorizontalThinBoxLine);
        }
        bottomcount.append(BottomRightThinCorner);
        WindowLines.push_back(bottomcount);
        
        
    }
    
}



std::string Window::returnWindowLine(int Line){
    
    return WindowLines.at(Line);
    
}
