#include "libtcod.hpp"
// size of the heightmap
#define MAIN_WIDTH 100
#define MAIN_HEIGHT 80
#define LIMIT_FPS 20
#include <math.h>

int playerX, playerY;


bool HandleKeys()
{
	TCOD_key_t Key = TCODConsole::checkForKeypress(true);
	bool quit = false;

	if(Key.vk == TCODK_ENTER && Key.lalt)
		TCODConsole::setFullscreen(!TCODConsole::isFullscreen());			

	switch(Key.vk)
	{
		case TCODK_UP:
			playerY--;
			break;


		case TCODK_DOWN:
			playerY++;
			break;

		case TCODK_LEFT:
			playerX--;
			break;

		case TCODK_RIGHT:
			playerX++;
			break;


		case TCODK_ESCAPE:
			quit = true;
			break;
	}
	return quit;
}


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
		
		quit = HandleKeys();
		if(quit) break;		

	}	

	return 0;
}
