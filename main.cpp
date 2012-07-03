#include "libtcod.hpp"
// size of the heightmap
#define HM_WIDTH 100
#define HM_HEIGHT 80
#define LIMIT_FPS 20
#include <math.h>


int main(int argc, char *argv[]) {
	TCODConsole::initRoot(HM_WIDTH,HM_HEIGHT,"The ASCII Project",false);
	TCODConsole::setCustomFont("arial10x10.png",TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
	TCODConsole::root->flush();
	TCODConsole::waitForKeypress(true);
	return 0;
}
