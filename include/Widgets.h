//
//  Widgets.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#ifndef The_ASCII_Project_Widgets_h
#define The_ASCII_Project_Widgets_h

#include <vector>
#include <string>

#include "Display.h"
#include "Window.h"



class Widget : public Frame {

private:
    
    
    
public:
    
    
    Widget(int x1, int y1, int x2, int y2, Window *tgt) : Frame(x1, y1, x2, y2, tgt){};
    
};





#endif
