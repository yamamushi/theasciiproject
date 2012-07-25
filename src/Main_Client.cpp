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




// Lets's Rock n' Roll

int main(int argc, char *argv[])
{

    // boring variables
    bool quit = false;

    // This is our custom Apple app building stuff
    
#ifdef __APPLE__
    macApp_setRelativePath();
#endif

    ClientMap *cMap = new ClientMap();

    GraphicsTCOD *output = new GraphicsTCOD(cMap);
    Keyboard *kboard = new Keyboard(0, 0);


    SocketHandler h;
    MapSocket *p = new MapSocket(h);
    p->loadClientMap(cMap);
    p->assignLocalOut(output);

    p->SetDeleteByHandler();

    printf("Trying to connect to server...\n");
    p->Open("theasciiproject.com", 5250);
    h.Add(p);
    h.Select(1, 0);

    // Main Game Loop
    while (!TCODConsole::isWindowClosed()) {

        //while (h.GetCount()) {

            h.Select(1, 0);

        //}

        output->render();
        output->clearScreen();

        quit = kboard->handleKeys();
        
        if (quit) {
            h.SetClose();
            break;
        }
    }

    return 0;
}
