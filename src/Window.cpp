//
//  Window.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//


#include <sstream>

#include "Window.h"
#include "Widgets.h"
#include "AnsiConstants.h"
#include "UnicodeConstants.h"



Window::Window(int x, int y, bool bordered){
    
    
    
    
    Width = x;
    Height = y;
    
    
    if(bordered)
    {
        std::string topbar, bottombar, endcount;
        std::stringstream end;
        
        end << Width;
        endcount = end.str();
                
        topbar = returnTopBar();
        
        
        WindowLines.push_back(topbar);
        
        for(int x=2; x < Height; x++)
        {
                        
            WindowLines.push_back(borderLine(x));
            
        }
    
        bottombar = returnBottomBar();
        WindowLines.push_back(bottombar);
        
    }
    
    Widget *shellFrame = new Widget(1, Height-2, Width, Height, this);
    shellFrame->FrameLines.push_back("\x1b[K\x1b[23H\u2503$> ");
    FrameList.push_back(shellFrame);
    
    Widget *colorBox = new Widget(75, 5, 85, 10, this);
    colorBox->fill(BACK_BLUE + FORE_WHITE + "\u2591" + FORE_GREEN + BACK_BLACK);
    drawFrame(colorBox);
    
    colorBox->move(-20, 0);
    colorBox->fill(BACK_BLUE + FORE_WHITE + "\u2591" + FORE_GREEN + BACK_BLACK);
    drawFrame(colorBox);
    
    
    colorBox->move(-3, 3);
    drawFrame(colorBox);
    
    
    Widget *sideFrame = new Widget(1, 1, 20, Height, this);
    drawFrame(sideFrame);
    
    drawFrame(*FrameList.begin());
    
    
    
}



std::string Window::returnWindowLine(int Line){
    
    return WindowLines.at(Line);
    
}


std::string Window::returnTopBar(){
    
    std::string topbar, endcount;
    std::stringstream end;
    end << Width;
    endcount = end.str();
    std::string tmp("\x1b[1G");
    tmp.replace(2, 1, endcount);
    
    topbar = "\377\375\x22\x1b[2J";
    topbar.append("\x1b[1H" + TopLeftThinCorner);
    for(int x=0; x < Width-2; x++)
    {
        topbar.append(HorizontalThinBoxLine);
    }
    topbar.append(tmp);
    topbar.append(TopRightThinCorner);
    
    return topbar;
    
}


std::string Window::returnBottomBar(){
    
    std::stringstream end;
    std::string endcount;
    std::string bottombar("\x1b[1H");
    end << Height;
    
    endcount = end.str();
    bottombar.replace(2, 1, endcount);
    bottombar.append(BottomLeftThinCorner);
    for(int x=0; x < Width-2; x++)
    {
        bottombar.append(HorizontalThinBoxLine);
    }
    bottombar.append(BottomRightThinCorner);
    
    return bottombar;
    
}


std::string Window::borderLine(int lineNumber){
    
    std::stringstream width, height;
    std::string beginLine, endLine, bCount, eCount;
    
    width << Width;
    height << lineNumber;
    
    bCount = height.str();
    beginLine = "\x1b[1H";
    beginLine.replace(2, 1, bCount);
    beginLine.append(VerticalThinBoxLine);
    
    eCount = width.str();
    endLine = "\x1b[1G";
    endLine.replace(2, 1, eCount);
    endLine.append(VerticalThinBoxLine + "\x1b[2G");
    
    std::string returnString(beginLine + endLine);
    return returnString;
    
    
}



void Window::drawFrame(Frame *frm){
    
    Frame *tgt = frm;
    
    int x1, y1, x2, y2;

    x1 = tgt->X1;
    x2 = tgt->X2;
    y1 = tgt->Y1;
    y2 = tgt->Y2;

    
    if(x1 < 1)
        x1 = 1;
    if(x2 > Width)
        x2 = Width;
    if(y1 < 1)
        y1 = 1;
    if(y2 > Height)
        y2 = Height;
    
    int fLine = 0;
    for(int y = y1; y < y2+1; y++)
    {
        std::string outputLine;
        
        std::stringstream line;
        line << y;
        
        std::string count;
        count = line.str();
        
        std::string outputY("\x1b[1H");
        outputY.replace(2, 1, count);
        
        outputLine.append(outputY);
        
                
        for(int x = x1; x < x2+1; x++)
        {
            std::stringstream column;
            column << x;
            
            std::string tmp;
            tmp = column.str();
            
            std::string outputX("\x1b[1G");
            outputX.replace(2, 1, tmp);
            
            outputLine.append(outputX);
            
            if((x == x1 || x == x2) && (y != y1 && y != y2))
                outputLine.append(VerticalThinBoxLine);
            
            
            if(y == y1 && x == x1)
            {
                if(x == 1 &&y != 1)
                    outputLine.append(LeftBoxTee);
                else
                    outputLine.append(TopLeftThinCorner);
                for(int i = 0; i < (x2-x1); i++)
                {
                    outputLine.append(HorizontalThinBoxLine);
                    
                }
                
            }
            
            if(y == y2 && x == x1)
            {
                if(x == 1)
                    outputLine.append(LeftBoxTee);
                else
                    outputLine.append(BottomLeftThinCorner);
                for(int i = 0; i < (x2-x1); i++)
                {
                    outputLine.append(HorizontalThinBoxLine);
                    
                }
                
            }
            
            if(y == y1 && x == x2)
            {
                if(x == Width && y != 1)
                    outputLine.append(RightBoxTee);
                else if( y == 1)
                    outputLine.append(TopDownTee);
                else
                    outputLine.append(TopRightThinCorner);
            }
            
            if(y == y2 && x == x2)
            {
                if(x == Width)
                    outputLine.append(RightBoxTee);
                else
                    outputLine.append(BottomRightThinCorner);
            }
            
            if(y > y1)
            {
                if(x == x1+1)
                    if( fLine-1 < tgt->FrameLines.size())
                        {
                            int buffLen, distanceX, len;
                            
                            std::string src, out;
                            
                            src = tgt->FrameLines.at(fLine-1);
                            buffLen = (int)src.length();
                            
                            len = x2 - x1;
                            distanceX = Width - x1;
                            
                            if(distanceX < len)
                            {
                                int diff;
                                
                                diff = len - distanceX;
                                
                                if(buffLen > diff)
                                {
                                   src.resize(buffLen); 
                                }
                            }
                                                                                      
                            
                            outputLine.append(src);
                            
                        }
                
            }
            
        }
        
        if(y < Height)
            WindowLines.at(y).append(outputLine);
        fLine++;
    }
    
    
}










Frame::Frame(int x1, int y1, int x2, int y2, Window *tgt){
    
    
    if(x1 == x2)
        return;
    else if(x1 < x2)
    {
        X1 = x1;
        X2 = x2;
    }
    else{
        X1 = x2;
        X2 = x1;
    }
    
    if(y1 == y2)
        return;
    else if(y1 < y2)
    {
        Y1 = y1;
        Y2 = y2;
    }
    else{
        Y1 = y2;
        Y2 = y1;
    }
    
    
    parentWindow = tgt;
    
    
}







void Frame::move(int x, int y, bool clear){
    
    X1 += x;
    X2 += x;

    Y1 += y;
    Y2 += y; 
    
    if(clear)
        ;
        //    fill(" ");
}


void Frame::resizeX(int x){
    
    X2 += x;    
    
}




void Frame::resizeY(int y){
    
    Y2 += y;   
}




void Frame::fill(std::string filler){
    
    FrameLines.clear();
    
    int length, lines;
    
    int x1, y1, x2, y2;
    

    x1 = X1;
    x2 = X2;
    y1 = Y1;
    y2 = Y2;
   
    
    
    if(x1 < 1)
        x1 = 1;
    if(x2 > parentWindow->Width)
        x2 = parentWindow->Width;
    if(y1 < 1)
        y1 = 1;
    if(y2 > parentWindow->Height)
        y2 = parentWindow->Height;
   
    
    length = x2 - x1 - 1;
    lines = y2 - y1 - 1;
    
    std::string fill;
    
    for(int x = 0; x < length; x++)
    {
        fill.append(filler);
    }
    
    for(int x = 0; x < lines; x++)
    {
        FrameLines.push_back(fill);
    }
    
    
    
}



