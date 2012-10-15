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
    
    Frame *tmpFrame = new Frame(5, 5, 15, 10);
    drawFrame(tmpFrame);
    
    Frame *wallFrame = new Frame(1, 15, 80, 20);
    drawFrame(wallFrame);
    
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
    
    if(tgt->X1 == tgt->X2)
        return;
    else if(tgt->X1 < tgt->X2)
    {
        x1 = tgt->X1;
        x2 = tgt->X2;
    }
    else{
        x1 = tgt->X2;
        x2 = tgt->X1;
    }
    
    if(tgt->Y1 == tgt->Y2)
        return;
    else if(tgt->Y1 < tgt->Y2)
    {
        y1 = tgt->Y1;
        y2 = tgt->Y2;
    }
    else{
        y1 = tgt->Y2;
        y2 = tgt->Y1;
    }
    
    
    
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
                if(x == 1)
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
                if(x == Width)
                    outputLine.append(RightBoxTee);
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
            
            
        }
        
        WindowLines.at(y).append(outputLine);
        
    }
    
    
}


