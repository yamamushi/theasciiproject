/*
 * =====================================================================================
 *
 *       Filename:  graphics.cpp
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


#include "headers.h"



GraphicsTCOD::GraphicsTCOD(Map *sourceMap, EntityMap *EntMap){
	init(sourceMap, EntMap);
}


void GraphicsTCOD::init(Map *sourceMap, EntityMap *EntMap){

	input = sourceMap;
	entMap = EntMap;
	
	
	
	
	
	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false,TCOD_RENDERER_SDL);
        TCODConsole *tmp = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);
        output = tmp;
	TCODConsole::root->setDefaultForeground(TCODColor::white);



}






void GraphicsTCOD::render(){

	entMap->refreshEntityMap();
	renderTiles();
	


	TCODConsole::blit(output, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
	TCODConsole::flush();


}    

	

void GraphicsTCOD::renderTiles(){
	
	c = new colorTableTCOD();
	
	int x, y;	
        for(x=0;x<MAP_WIDTH;x++){                                                                         
                for(y=0;y<MAP_HEIGHT;y++){                                                                
                        if (input->virtMap[x][y]->is_explored()){                                       
				if (input->virtMap[x][y]->is_sight_blocked()){        
				     	output->setCharBackground(x, y, c->color(DARK_WALL));
					     	if (input->virtMap[x][y]->visible){    
						     	output->setCharBackground(x, y, c->color(LIGHT_WALL)); 
						}                                                     
				}
				else{
					output->setCharBackground(x, y, c->color(DARK_GROUND)); 
					if (input->virtMap[x][y]->visible){          
						output->setCharBackground(x, y, c->color(LIGHT_GROUND));  
				     	}                                  
				}                                                        
			}                                                  
		}                  
	}


	int color;
	char *ent;


	for (x = 0; x < MAP_WIDTH; x++){
		for (y = 0; y < MAP_HEIGHT; y++){
			if(entMap->checkOccupied(x, y)){
				current = entMap->outputEntity(x, y);
				int color = current->getColor();
				output->setDefaultForeground(c->color(DARK_GROUND));
				output->print(x, y, current->getSymbol());
			}
		}
	}
}


void GraphicsTCOD::clearScreen(){

	output->clear();

}













