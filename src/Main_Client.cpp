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

// First our custom headers
//
#include "Headers.h"
#include "Platform.h"


// Our ASIO tcp object
using boost::asio::ip::tcp;



// Lets's Rock n' Roll!!!

int main(int argc, char *argv[])
{
    // This is our custom Apple app building stuff
#ifdef __APPLE__
    macApp_setRelativePath();
#endif
    
    ClientMap *cMap = new ClientMap;
    GraphicsTCOD *output = new GraphicsTCOD(cMap);
    
    
    
    
    
    try
    {
        boost::asio::io_service io_service;
        
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("localhost", "5250");
        tcp::resolver::iterator iterator = resolver.resolve(query);
        
        
        ClientSession c(io_service, iterator, cMap, output);
        boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
        
        Keyboard *kboard = new Keyboard(&c);
        
        // Main Game Loop
        while (!TCODConsole::isWindowClosed()) {
            
            //c.set_paused(true);
                        
            output->render();
            //output->clearScreen();
            
            //c.set_paused(false);
            
            
            bool quit = kboard->handleKeys();
            
            if (quit)
            {
                c.close();
                t.join();
                break;
            }
            
            
                        
        }
    }
    catch (std::exception& e)
    {
        cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}
