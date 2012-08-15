#include "Headers.h"



// x and y are our positions on the screen, w and h are our width and height.
ScrollBox::ScrollBox( int x, int y, int w, int h) : Widget(x,y,w,h)
{
 
    textBuffer = new std::vector<std::string>;
    
}



ScrollBox::~ScrollBox()
{
    
    if(!textBuffer->empty())
    {
        
        
    }
    
    
}


void ScrollBox::update(const TCOD_key_t k)
{
    if ( keyboardFocus == this )
    {
        
    }
    
    
}


void ScrollBox::insertText(std::string newText)
{
    
    if(textBuffer)
    {
        textBuffer->push_back(newText);
    }
    
}


void ScrollBox::render(TCODConsole *console)
{
    
    console->setDefaultBackground(back);
    console->setDefaultForeground(fore);
    console->printFrame(x,y,w,h,true,TCOD_BKGND_SET);
    console->print(x+w-2, y+1, L"\u21E7");
    console->print(x+w-2, y+h-2, L"\u21E9");
    
    if(!textBuffer->empty())
    {
        std::string tmpString = textBuffer->back();
        if(tmpString.length() > w)
            tmpString.insert(w-3, "\n");
        
        if(tmpString == "/quit")
            exit(0);
            
        console->print(x+1, y+1, (const char*)&tmpString[0]);
    }
    
    
}


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















