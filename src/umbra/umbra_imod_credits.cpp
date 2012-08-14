#include "umbra.hpp"

UmbraModCredits::UmbraModCredits() {
	coords.set(0,0);
	con = new TCODConsole(40,1);
}

void UmbraModCredits::onActivate() {
	startTime = TCODSystem::getElapsedMilli();
}

bool UmbraModCredits::update() {
	alpha = 2.0f - (float)(TCODSystem::getElapsedMilli() - startTime) / (float)duration;
	alpha = MIN(1.0f,alpha);
	if (alpha >= 0.0f) return true;
	else return false;
}

void UmbraModCredits::render() {
	static const char * str = "Powered by "UMBRA_TITLE" "UMBRA_VERSION" "UMBRA_STATUS;
	con->setDefaultForeground(TCODColor(250,250,220));
	con->printEx(0,0,TCOD_BKGND_NONE,TCOD_LEFT,str);
	TCODConsole::blit(con,0,0,strlen(str),1,TCODConsole::root,coords.x,coords.y,alpha,0.0f);
}

void UmbraModCredits::set(int x, int y, uint32 d) {
	duration = d/2;
	coords.set(x,y);
}
