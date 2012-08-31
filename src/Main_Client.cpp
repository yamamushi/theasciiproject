/*
 * =====================================================================================
 *
 *       Filename:  Main.cpp
 *
 *    Description:  The ASCII Project main loop
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:04:46 AM
 *       Revision:  07/30/2012
 *       Compiler:  gcc
 *
 *         Author:  Yamamushi (Jon Rumion)
 *   Organization:  The ASCII Project
 *
 *	  License:  GPLv3
 *
 *	  Copyright 2012 Jonathan Rumion
 *
 *   This file is part of The ASCII Project.
 *
 *   The ASCII Project is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   The ASCII Project is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with The ASCII Project.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * =====================================================================================
 */

#include <iostream>

#include "libtcod/libtcod.hpp"
#include "Platform.h"

#include "Graphics.h"
#include "ClientMap.h"


GraphicsTCOD *graphicsEngine;
ClientMap *cMap;


// Lets's Rock n' Roll!!!

int main(int argc, char *argv[])
{
    // This is our custom Apple app building stuff
#ifdef __APPLE__
    macApp_setRelativePath();
#endif
    
    cMap = new ClientMap;
    graphicsEngine = new GraphicsTCOD(cMap);
    
    
    try
    {
        
        graphicsEngine->drawMenu();
        
        
        while(!TCODConsole::isWindowClosed())
        {
            graphicsEngine->drawMainInterface();
        }
        
        
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}
