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


#include "headers.h"




GraphicsTCOD::GraphicsTCOD(TileMap *sourceMap, EntityMap *EntMap, Entity *player){
	init(sourceMap, EntMap, player);
}


void GraphicsTCOD::init(TileMap *sourceMap, EntityMap *EntMap, Entity *player){

	input = sourceMap;
	entMap = EntMap;
	localPlayer = player;

        setlocale(LC_ALL, "");

	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false,TCOD_RENDERER_SDL);
        TCODConsole *tmp = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);
        output = tmp;
        TCODConsole::root->setCustomFont("consolas_unicode_12x12", TCOD_FONT_LAYOUT_ASCII_INROW);
        //TCODConsole::root->setCustomFont("font.png", TCOD_FONT_LAYOUT_ASCII_INROW, 32, 372);
       // TCOD_console_print_ex_utf(NULL, 3, 3, TCOD_BKGND_SET, TCOD_LEFT, L"☺");

        output->mapAsciiCodesToFont(0, 11904, 1, 1);

	//TCODConsole::root->setDefaultForeground(TCODColor::white);



}






void GraphicsTCOD::render(){

	entMap->refreshEntityMap();

	renderTiles();
	renderEntities();



	TCODConsole::blit(output, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
	TCODConsole::flush();


}



void GraphicsTCOD::renderTiles(){

	int x, y;

	// These are for our HSV mappings
	float H, S, V;
	float HD, SD, VD;



	for(x=0;x<MAP_WIDTH;x++){
                for(y=0;y<MAP_HEIGHT;y++){
                        if (input->virtMap[x][y]->is_explored()){

					H = input->virtMap[x][y]->H;
					HD = input->virtMap[x][y]->HD;
					S = input->virtMap[x][y]->S;
					SD = input->virtMap[x][y]->SD;
					V = input->virtMap[x][y]->V;
					VD = input->virtMap[x][y]->VD;

				if (input->virtMap[x][y]->is_sight_blocked()){
				     	output->setCharBackground(x, y, TCODColor(HD, SD, VD));
					     	if (input->virtMap[x][y]->visible){
						     		output->setCharBackground(x, y, TCODColor(H, S, V));
						}
				}
				else{
					output->setCharBackground(x, y, TCODColor(HD, SD, VD));
					if (input->virtMap[x][y]->visible){
						output->setCharBackground(x, y, TCODColor(H, S, V));
				     	}
				}
			}
		}
	}

}



void GraphicsTCOD::renderEntities(){

	int x, y;
	float H, S, V;
	wchar_t *symbol;

	x = localPlayer->posX();
	y = localPlayer->posY();

	H = localPlayer->H;
	S = localPlayer->S;
	V = localPlayer->V;

	output->setDefaultForeground(TCODColor(H, S, V));

	symbol = localPlayer->getSymbol();


	//output->putChar(x, y, 34);
        //wchar_t *tst = L"\u263A";
        //output->printEx(NULL, x, y, TCOD_BKGND_SET, TCOD_LEFT, "2639");
        output->print(x, y, symbol);



	for (x=0;x<MAP_WIDTH;x++){
		for(y=0;y<MAP_HEIGHT;y++){
			if (localPlayer->isInitialized()){
				if ( !(x == localPlayer->posX()) || !(y == localPlayer->posY()) ){
			       		if (localPlayer->fov[x][y]){
						if ( (entMap->checkOccupied(x, y)) ){
							scan = entMap->outputLastEntity(x, y);
							H = scan->H;
							S = scan->S;
							V = scan->V;
							output->setDefaultForeground(TCODColor(H, S, V));
							symbol = scan->getSymbol();
							output->print(x, y, symbol);
						}
					}
				}
			}
		}
	}
}

















void GraphicsTCOD::clearScreen(){

	output->clear();

}













