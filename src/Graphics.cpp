/*
 * =====================================================================================
 *
 *       Filename:  Graphics.cpp
 *
 *    Description:  Our graphics handling library that relies on libtcod.
 *    		The intention is for this library to handle all reliance on
 *    		the libtcod graphics functions - thereby slowly modularilizing
 *    		the client to be rendered differently.
 *
 *        Version:  1.0
 *        Created:  07/05/2012
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


#include "Headers.h"




GraphicsTCOD::GraphicsTCOD(ClientMap *clientMap){
	init(clientMap);
}

void GraphicsTCOD::init(ClientMap *clientMap){
    
    cMap = clientMap;
    
    
    setlocale(LC_ALL, "en_US.UTF-8");
    TCODConsole::setCustomFont("data/font.png", TCOD_FONT_LAYOUT_ASCII_INROW, 32, 2048);
    
	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false,TCOD_RENDERER_SDL);
    //	TCODConsole::credits();
    
    TCODConsole *mainConsole = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);
    output = mainConsole;
    
    offScreenConsole = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);
    
    
}

void GraphicsTCOD::render(){
    
    //TCODConsole::blit(offScreenConsole, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
    
	TCODConsole::blit(output, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
	TCODConsole::flush();
    
}

void GraphicsTCOD::flushScreen(){
    TCODConsole::flush();
    
}

void GraphicsTCOD::drawAt(int x, int y)
{
    if(cMap->cMap[x][y] != nullptr)
    {
        if (cMap->returnExplored(x, y)){
            
            if (cMap->returnOccupied(x, y)){
                H = cMap->returnH(x, y);
                S = cMap->returnS(x, y);
                V = cMap->returnV(x, y);
                output->setDefaultForeground(TCODColor(H, S, V));
                
                
                try
                {
                    
                    output->print(x, y, cMap->cMap[x][y]->symbol);
                    
                }
                catch (std::exception& e)
                {
                    cerr << "Exception: " << e.what() << "\n";
                }
            }
            
            
            else{
                if (cMap->returnVisible(x, y)){
                    H = cMap->returnH(x, y);
                    S = cMap->returnS(x, y);
                    V = cMap->returnV(x, y);
                    output->setCharBackground(x, y, TCODColor(0,0,0));
                    output->setDefaultForeground(TCODColor(H, S, V));
                    
                    try
                    {
                        
                        output->print(x, y, cMap->cMap[x][y]->symbol);
                        
                        
                    }
                    catch (std::exception& e)
                    {
                        cerr << "Exception: " << e.what() << "\n";
                    }
                    
                    
                    
                    
                }
                else{
                    HD = cMap->returnHD(x, y);
                    SD = cMap->returnSD(x, y);
                    VD = cMap->returnVD(x, y);
                    output->setCharBackground(x, y, TCODColor(0,0,0));
                    output->setDefaultForeground(TCODColor(HD, SD, VD));
                    
                    try
                    {
                        
                        output->print(x, y, cMap->cMap[x][y]->symbol);
                        
                        
                    }
                    catch (std::exception& e)
                    {
                        cerr << "Exception: " << e.what() << "\n";
                    }
                    
                }
            }
        }
    }
}

void GraphicsTCOD::drawAll(){
    
    for(int x = 0; x < MAP_WIDTH; x++)
    {
        for(int y=0; y < MAP_HEIGHT; y++)
        {
            
            drawAt(x, y);
        }
    }
    
    
}





void GraphicsTCOD::prepare(int x, int y){
    
    
    if (!cMap->returnVisible(x, y) && cMap->returnExplored(x, y))
    {
        HD = cMap->returnHD(x, y);
        SD = cMap->returnSD(x, y);
        VD = cMap->returnVD(x, y);
        output->setCharBackground(x, y, TCODColor(0,0,0));
        output->setDefaultForeground(TCODColor(HD, SD, VD));
        
        output->print(x, y, cMap->cMap[x][y]->symbol);
        
    }
}



void GraphicsTCOD::clearScreen(){
    
	output->clear();
    
}













