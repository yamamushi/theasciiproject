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


class Frame;



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
    
    void render();
    
    
};



class Frame{
    
private:
    
    
public:
    
    std::vector<std::string> FrameLines;
    
    int X1, X2, Y1, Y2;
    Window *parentWindow;
    
    Frame(int x1, int y1, int x2, int y2, Window *tgt);
    
    void move(int x, int y, bool clear=true);
    void resizeX(int x);
    void resizeY(int y);
    
    void fill(std::string filler);
    
};





#endif
