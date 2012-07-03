/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
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
 * =====================================================================================
 */

// First our custom headers
#include "libtcod.hpp"
#include "keyboard.h"

// Followed by standard headers
#include <math.h>

// size of the heightmap
#define MAIN_WIDTH 100
#define MAIN_HEIGHT 80

#define LIMIT_FPS 20

// We'll probably move these global variables somewhere else later
int playerX, playerY;


int main(
	int argc, char *argv[]) {


	// boring variables
	bool quit = false;
	playerX = MAIN_WIDTH/2;
	playerY = MAIN_HEIGHT/2;

	
	// Let's get things setup
	
	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false);
	// TCODConsole::credits();
	
	TCODConsole *con = new TCODConsole(MAIN_WIDTH, MAIN_HEIGHT);

	
	TCODSystem::setFps(LIMIT_FPS);


	// We'll set the foreground color once now and modify it as necessary when in our game loop
	TCODConsole::root->setDefaultForeground(TCODColor::white);	

	while(!TCODConsole::isWindowClosed()) {
		
		con->printEx(playerX, playerY, TCOD_BKGND_NONE, TCOD_LEFT, "@");
		TCODConsole::flush();
		
		TCODConsole::blit(con, 0, 0, MAIN_WIDTH, MAIN_HEIGHT, TCODConsole::root, 0, 0);

		con->print(playerX, playerY, " ");
		
		quit = handleKeys();
		if(quit) break;		

	}	

	return 0;
}
