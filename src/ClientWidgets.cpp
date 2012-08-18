#include "Headers.h"


using boost::asio::ip::tcp;



// x and y are our positions on the screen, w and h are our width and height.
ScrollBox::ScrollBox( int x, int y, int w, int h, int MaxBuffer, TCODConsole *Console, ClientMap *cMap, GraphicsTCOD *graphicsEngine) : Widget(x,y,w,h)
{
    
    maxBuffer = MaxBuffer;
    textBuffer = new std::vector<std::string>;
    console = Console;
    scrollBuffer = 0;
    acceptCommands = false;
    connected = false;
    
    graphics = graphicsEngine;
    clientMap = cMap;
}



ScrollBox::~ScrollBox()
{
    
    if(!textBuffer->empty())
    {
        textBuffer->clear();
        delete textBuffer;
        
    }
    
    
}


void ScrollBox::setRealPosition(int x, int y)
{
    
    realX = x;
    realY = y;
    
}


void ScrollBox::update(const TCOD_mouse_t k)
{
    
    if (mouse.cx == realX + w - 2 && mouse.cy == realY + 1)
    {
        onUpArrow = true;
        //cout << "Up" << endl;
    }
    else if (mouse.cx == realX + w - 2 && mouse.cy == realY + h - 2 )
    {
        onDownArrow = true;
        //cout << "Down" << endl;
    }
    else
    {
        onUpArrow = false;
        onDownArrow = false;
    }
    
    
    if(k.lbutton)
    {
        onButtonPress();
    }
    
    if(k.wheel_up)
        onScrollUp();
    
    if(k.wheel_down)
        onScrollDown();
}


void ScrollBox::attachConsole(TCODConsole *Console)
{
    console = Console;
}

void ScrollBox::takeCommands(bool accept)
{
    acceptCommands = accept;
}

void ScrollBox::insertText(std::string newText)
{
    
    if(textBuffer)
    {
        if(textBuffer->size() >= maxBuffer)
            textBuffer->erase(textBuffer->begin());
        
        std::string fixedLengthText;
        
        if(newText.length() > (w-4))
        {
           // fixedLengthText = "Too Big\nPlease Try Again";
            
          //  char *fixMe = new char[w];
            int range = 0;
            for(int i = 0; i < newText.length(); i++)
            {
                 
                if(newText.at(i) == '\n' || i == newText.length()-1)
                {
                    //cout << "new line!" << endl;

                    
                    
                    if(range > (w-4))
                    {
                        //cout << range - (w-4) << endl;
                        int diff = range - (w-5);
                        
                        std::string temp(newText.begin()+(i-range), newText.begin()+(i-diff));
                        cout << temp << endl;
                        
                        textBuffer->push_back(temp);
                        
                        std::string temp2(newText.begin()+(i-diff), newText.begin()+(i));
                        cout << temp2 << endl;
                        
                        textBuffer->push_back(temp2);
                        range = 0;
                    }
                    
                    else if(newText.at(i) == '\n' )
                    {
                        newText.replace(i, 1, " ");
                        if(i - range + 1 >= 0 )//&& i - range + 1 < i)
                        {
                            std::string temp(newText.begin()+(i - range), newText.begin()+(i));
                            textBuffer->push_back(temp);
                            range = 0;
                        }
                        else
                        {
                            std::string temp(newText.begin()+(i - range), newText.begin()+(i));
                            textBuffer->push_back(temp);
                            range = 0;
                        }
                    }
                    else
                    {
                        if(i - range + 1 >= 0 )//&& i - range + 1 < i)
                        {
                            std::string temp(newText.begin()+(i - range), newText.begin()+(i));
                            textBuffer->push_back(temp);
                            range = 0;
                        }
                        else
                        {
                            std::string temp(newText.begin()+(i - range), newText.begin()+(i));
                            textBuffer->push_back(temp);
                            range = 0;
                        }
                    }

                }
                
                range++;
            }
        }
        else
        {
            for(int i =0; i < newText.length(); i++)
            {
                if(newText.at(i) == '\r' || newText.at(i) == '\n')
                    newText.replace(i, 1, " ");
                
            }
                
            
            
            fixedLengthText = newText;
            textBuffer->push_back(fixedLengthText);
        }
        
        
    }
    
}


void ScrollBox::render()
{
    
    console->setDefaultBackground(back);
    console->setDefaultForeground(fore);
    
    console->setColorControl(TCOD_COLCTRL_1, TCODColor(255,255,255), TCODColor(0,0,0));
    console->printFrame(x,y,w,h,true,TCOD_BKGND_SET);
    console->print(x+w-2, y+1, L"\u21E7", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    console->print(x+w-2, y+h-2, L"\u21E9", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    
    console->setColorControl(TCOD_COLCTRL_2, TCODColor(0,255,0), TCODColor(0,0,0));
    
    
    if(!textBuffer->empty())
    {
        
        std::string checkForCommand = textBuffer->back();
        
        if(acceptCommands)
        {
            if(checkForCommand == ".exit")
            {
                exit(0);
            }
            
            if(checkForCommand == ".clear")
            {
                scrollBuffer = 0;
                textBuffer->clear();
            }
            
        }
        
        
        
        if(textBuffer->size() > h - 2)  // we ignore the top and the bottom positions.
        {
            for(int i=1; i < h - 1; i++)     // The "-3" is to account for i+1+y potentially overflowwing.
            {                              // We start at i=1 ot account for the vector at position 0
                
                std::string tmpString;
                if(((int)textBuffer->size() - i - scrollBuffer) >= 0)
                {
                    tmpString = textBuffer->at((textBuffer->size())-i-scrollBuffer);
                }
                else
                {
                    break;
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
                
                tmpString.insert(0, "%c");
                tmpString.append("%c");
                
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
    if(textBuffer->size() > h - 2)  // we ignore the top and the bottom positions.
    {
        if(onUpArrow)
        {
            if(scrollBuffer < maxBuffer && scrollBuffer < textBuffer->size() - h + 2)
                scrollBuffer++;
        }
        else if(onDownArrow)
        {
            if(scrollBuffer > 0)
                scrollBuffer--;
        }
    }
}


void ScrollBox::onButtonRelease()
{
    
}


void ScrollBox::onScrollUp()
{
    if(scrollBuffer < maxBuffer && scrollBuffer < textBuffer->size() - h + 2)
        scrollBuffer++;
}


void ScrollBox::onScrollDown()
{
    if(scrollBuffer > 0)
        scrollBuffer--;
}















