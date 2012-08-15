#include "Headers.h"



// x and y are our positions on the screen, w and h are our width and height.
ScrollBox::ScrollBox( int x, int y, int w, int h, int MaxBuffer, TCODConsole *Console) : Widget(x,y,w,h)
{
    
    maxBuffer = MaxBuffer;
    textBuffer = new std::vector<std::string>;
    console = Console;
    
}



ScrollBox::~ScrollBox()
{
    
    if(!textBuffer->empty())
    {
        textBuffer->clear();
        delete textBuffer;
        
    }
    
    
}


void ScrollBox::update(const TCOD_key_t k)
{
    if ( keyboardFocus == this )
    {
        
    }
    
}


void ScrollBox::attachConsole(TCODConsole *Console)
{
    console = Console;
}


void ScrollBox::insertText(std::string newText)
{
    
    if(textBuffer)
    {
        textBuffer->push_back(newText);
    }
    
}


void ScrollBox::render()
{
    
    console->setDefaultBackground(back);
    console->setDefaultForeground(fore);
    console->printFrame(x,y,w,h,true,TCOD_BKGND_SET);
    console->print(x+w-2, y+1, L"\u21E7");
    console->print(x+w-2, y+h-2, L"\u21E9");
    
    console->setColorControl(TCOD_COLCTRL_2, TCODColor(0,255,0), TCODColor(0,0,0));
    
    
    if(!textBuffer->empty())
    {
        if(textBuffer->size() == maxBuffer)
            textBuffer->erase(textBuffer->begin());
        
        std::string checkForCommand = textBuffer->back();
        
        if(checkForCommand == "/quit")
            exit(0);
        
        if(textBuffer->size() > h - 2)  // we ignore the top and the bottom positions.
        {     
            for(int i=1; i < h - 1; i++)     // The "-3" is to account for i+1+y potentially overflowwing.
            {                              // We start at i=1 ot account for the vector at position 0
                
                
                std::string tmpString = textBuffer->at((textBuffer->size())-i);
                
                int stringLength = (int)tmpString.length();
                
                
                if(stringLength >= w)
                {
                    int size = stringLength/w;
                    
                    for(x = 1; x < size; x++)
                        tmpString.insert((x*w)-3, "\n");
                }
                
                tmpString.insert(0, "%c");
                tmpString.insert(tmpString.length(), "%c");
                
                console->print(x+1, h-1-i, (const char*)&tmpString[0], TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
                
            }
            
        }
        
        else
        {
            for(int i=1; i < textBuffer->size()+1; i++)     // The "-3" is to account for i+1+y potentially overflowwing.
            {                              // We start at i=1 ot account for the vector at position 0
                
                
                std::string tmpString = textBuffer->at((textBuffer->size())-i);
                
                int stringLength = (int)tmpString.length();
                
                
                if(stringLength >= w)
                {
                    int size = stringLength/w;
                    
                    for(x = 1; x < size; x++)
                        tmpString.insert((x*w)-3, "\n");
                }
                
                tmpString.insert(0, "%c");
                tmpString.insert(tmpString.length(), "%c");
                
                console->print(x+1, h-1-i, (const char*)&tmpString[0], TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
                
            }
        }
    }
    
    
}


/*
 
 Making note of this for my own memory, the purpose of having to specify
 the console at class initialization is so that the following functions
 work properly.
 
 */

void ScrollBox::onButtonPress()
{
    
}


void ScrollBox::onButtonRelease()
{
    
}


void ScrollBox::onScrollUp()
{
    
}


void ScrollBox::onScrollDown()
{
    
}















