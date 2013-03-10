/*
 
 The ASCII Project - Client
 
 Right now this is a shell example taken from 
 http://doryen.eptalys.net/forum/index.php?topic=1414.0
 
 With special thanks to "DrKillPatient" of the Doryen Forums.
 
 */

#include "libtcod.hpp"
#include "platform.h"

int main()
{
    // Set the path to the Resources folder in the app bundle if on a Mac
#ifdef __APPLE__
    macApp_setRelativePath();
#endif
    
    // initialize the libtcod root console and set the font
    const char *font="./data/fonts/terminal8x8_gs_ro.png";
    TCODConsole::setCustomFont(font, TCOD_FONT_LAYOUT_ASCII_INROW, 0, 0);
    TCODConsole::initRoot(128, 80, "libtcod Mac test", false);
    
    // draw to TCODConsole::root
    TCODConsole::root->setDefaultForeground(TCODColor::white);
    int c = 0;
    while(c < 255) {
        for(int y = 0; y < 16; y++) {
            for(int x = 0; x < 16; x++) {
                TCODConsole::root->putCharEx(x, y, c, TCODColor::white, TCODColor::black);
                ++c; // increment character number
            }
        }
    }
    TCODConsole::flush();
    TCODConsole::waitForKeypress(true);
    TCODConsole::credits();
    TCODConsole::flush();
    //TCODConsole::waitForKeypress(true);

}
