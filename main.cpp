#include "libtcod.hpp"
// size of the heightmap
#define MAIN_WIDTH 100
#define MAIN_HEIGHT 80
#define LIMIT_FPS 20
#include <math.h>

bool HandleKeys()
{
	TCOD_key_t Key = TCODConsole::waitForKeypress(true);

	bool quit = false;
	switch(Key.vk)
	{
		case TCODK_ESCAPE:
			quit = true;
			break;
	}
	return quit;
}



int main(
	int argc, char *argv[]) {

	bool quit = false;

	
	// Let's get things setup
	
	TCODConsole::initRoot(MAIN_WIDTH,MAIN_HEIGHT,"The ASCII Project",false);
	// TCODConsole::setCustomFont("arial10x10.png",TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
	TCODSystem::setFps(LIMIT_FPS);
	
	// We'll set the foreground color once now and modify it as necessary when in our game loop
	TCODConsole::root->setDefaultForeground(TCODColor::white);	


	while(!TCODConsole::isWindowClosed()) {
		TCODConsole::root->print(1,1,"@");				
		
		TCODConsole::root->flush();

		quit = HandleKeys();
		if(quit) break;		

	}	


	TCODConsole::waitForKeypress(true);
	return 0;
}
