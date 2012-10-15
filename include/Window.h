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


class Frame {
    
private:
    
    
public:

    int X1, X2, Y1, Y2;
    
    Frame(int x1, int y1, int x2, int y2){X1 = x1; X2 = x2; Y1 = y1; Y2 = y2;};
    
    
};





class Window {
    
private:
    
    
    
    
    
public:
    
    int Width, Height;

    std::vector<std::string> WindowLines;
    std::vector<Frame *> FrameList;
    
    Window(int x, int y, bool bordered=false);
    virtual ~Window(){};
    
    std::string returnWindowLine(int Line);
    std::string returnTopBar();
    std::string returnBottomBar();
    std::string borderLine(int lineNumber);
    
    void drawFrame(Frame *frm);
    
    
};








#endif
