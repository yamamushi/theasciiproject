/*
 * =====================================================================================
 *
 *       Filename:  Main.cpp
 *
 *    Description:  The ASCII Project main loop
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:04:46 AM
 *       Revision:  none
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
#include "headers.h"
#include "Platform.h"

// Our ASIO tcp object
using boost::asio::ip::tcp;


// Lets's Rock n' Roll

int main(int argc, char *argv[])
{
    // This is our custom Apple app building stuff
#ifdef __APPLE__
    macApp_setRelativePath();
#endif
    
    ClientMap *cMap = new ClientMap();
    
    GraphicsTCOD *output = new GraphicsTCOD(cMap);
    //Keyboard *kboard = new Keyboard(0, 0);
    ClientMapPacker *packer = new ClientMapPacker();    

    // io_service for Boost::ASIO
    boost::asio::io_service io_service;
    // Next we attach our io_service to our resolver
    tcp::resolver resolver(io_service);
    tcp::resolver::query query("theasciiproject.com", "5250");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);
    // At this point our connection to our server should be open.
    
    for (;;)
    {
        //char buf[128];
        boost::array<char, 128> buf;
        boost::system::error_code error;
        //size_t bytes_transferred =
        socket.receive(boost::asio::buffer(buf));
        //char *buf = new char[128];
        boost::asio::const_buffer b1 = boost::asio::buffer(buf);
        const unsigned char* p1 = boost::asio::buffer_cast<const unsigned char*>(b1);
        packer->unpackFromNet(cMap, (unsigned char*)p1);
        output->render();
    }
    
    
    
    
    // Main Game Loop
 /*   while (!TCODConsole::isWindowClosed()) {
    
        
        output->render();
        output->clearScreen();
        
        bool quit = kboard->handleKeys();
        
        if (quit)
            break;
        
    }
    */
    
    return 0;
}
