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




GraphicsTCOD::GraphicsTCOD(ClientMap *clientMap){
	init(clientMap);
}

void GraphicsTCOD::init(ClientMap *clientMap){

        cMap = clientMap;

        setlocale(LC_ALL, "en_US.UTF-8");
        TCODConsole::setCustomFont("data/font.png", TCOD_FONT_LAYOUT_ASCII_INROW, 32, 2048);

	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false,TCOD_RENDERER_SDL);
        //	TCODConsole::credits();

        TCODConsole *tmp = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);
        output = tmp;



}

void GraphicsTCOD::render(){

        prepare();

	TCODConsole::blit(output, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);
	TCODConsole::flush();


}

void GraphicsTCOD::prepare(){

    int x, y;



    for(x=0;x<MAP_WIDTH;x++){
        for(y=0;y<MAP_HEIGHT;y++){

            if (cMap->returnExplored(x, y)){

                H = cMap->returnH(x, y);
                S = cMap->returnS(x, y);
                V = cMap->returnV(x, y);

                wchar_t *sym;
                sym = cMap->cMap[x][y]->symbol;

                //printf("Symbol is %S", cMap->cMap[x][y]->symbol);
                if (cMap->returnOccupied(x, y)){

                        output->setDefaultForeground(TCODColor(H, S, V));
                        output->print(x, y, sym);
                }
                else{
                    HD = cMap->returnHD(x, y);
                    SD = cMap->returnSD(x, y);
                    VD = cMap->returnVD(x, y);

                    if (cMap->returnVisible(x, y)){
                        output->setCharBackground(x, y, TCODColor(0,0,0));
                        output->setDefaultForeground(TCODColor(H, S, V));
                        output->print(x, y, sym);
                    }

                    else{
                        output->setCharBackground(x, y, TCODColor(0,0,0));
                        output->setDefaultForeground(TCODColor(HD, SD, VD));
                        output->print(x, y, sym);
                    }
                }
            }

        }
    }


}





/*
void GraphicsTCOD::renderTiles(){

	int x, y;

	// These are for our HSV mappings
	float H, S, V;
	float HD, SD, VD;



	for(x=0;x<MAP_WIDTH;x++){
                for(y=0;y<MAP_HEIGHT;y++){
                        if (input->virtMap[x][y]->isExplored()){

					H = input->virtMap[x][y]->H;
					HD = input->virtMap[x][y]->HD;
					S = input->virtMap[x][y]->S;
					SD = input->virtMap[x][y]->SD;
					V = input->virtMap[x][y]->V;
					VD = input->virtMap[x][y]->VD;

				if (input->virtMap[x][y]->isSightBlocked()){
				     	output->setCharBackground(x, y, TCODColor(HD, SD, VD));
					     	if (input->virtMap[x][y]->visible){
						    output->setCharBackground(x, y, TCODColor(0,0,0));
                                                    output->setDefaultForeground(TCODColor(H, S, V));
                                                    wchar_t *symbol = input->virtMap[x][y]->getSymbol();
                                                    output->print(x, y, symbol);
						}
				}
				else{
					output->setCharBackground(x, y, TCODColor(HD, SD, VD));
					if (input->virtMap[x][y]->visible){
						output->setCharBackground(x, y, TCODColor(0, 0, 0));
                                                output->setDefaultForeground(TCODColor(H, S, V));
                                                wchar_t *symbol = input->virtMap[x][y]->getSymbol();
                                                output->print(x, y, symbol);

				     	}
				}
			}
		}
	}

}

void GraphicsTCOD::renderEntities(){

	int x, y;

	wchar_t *symbol;

	x = localPlayer->posX();
	y = localPlayer->posY();

	H = localPlayer->H;
	S = localPlayer->S;
	V = localPlayer->V;
	output->setDefaultForeground(TCODColor(H, S, V));

	symbol = localPlayer->getSymbol();
        //output->setCharBackground(x, y, TCODColor(TH, TS, TV));


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

                                                        //TH = input->virtMap[x][y]->H;
                                                        //TS = input->virtMap[x][y]->S;
                                                        //TV = input->virtMap[x][y]->V;
                                                        //output->setCharBackground(x, y, TCODColor(TH, TS, TV));


							symbol = scan->getSymbol();
							output->print(x, y, symbol);
						}
					}
				}
			}
		}
	}
}
*/

void GraphicsTCOD::clearScreen(){

	output->clear();

}













