//
//  Display.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#ifndef The_ASCII_Project_Display_h
#define The_ASCII_Project_Display_h

#include <string>
#include <vector>
#include "Window.h"
#include "Widgets.h"



class Display {
  
private:
    
    
public:
    
    int Width, Height;
    bool inputShell;
    Window *MainWindow;
    
    std::vector<std::string> DisplayLines;
    
    
    Display(int x, int y);
    virtual ~Display();
    
    
    void InitDisplay();
    
    std::string returnDisplay();
    std::string returnDisplay(int x);

    
    
};






#endif
