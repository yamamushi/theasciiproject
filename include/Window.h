//
//  Window.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#ifndef The_ASCII_Project_Window_h
#define The_ASCII_Project_Window_h


#include <vector>
#include <string>

class Window {
    
private:
    
    
    
    
    
public:
    
    int Width, Height;

    std::vector<std::string> WindowLines;
    
    Window(int x, int y, bool bordered=false);
    virtual ~Window(){};
    
    std::string returnWindowLine(int Line);
    
    
    
};





#endif
